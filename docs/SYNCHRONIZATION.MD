# Portable Synchronization Providers

## Purpose and scope

`EDP-Platform-Portable` supplies Standard C++ concrete implementations of the `EDP-Platform` synchronization capabilities.

The provider family is:

```text
Mutex
RecursiveMutex
ReadWriteMutex
CountingSemaphore
Signal
SpinLock
```

These implementations use only C++17 standard-library facilities and contain no Arduino, ESP-IDF, or FreeRTOS API calls.

## Composition contract

The providers advertise a nominal finite-wait resolution of:

```text
1 nanosecond
```

because finite waits are expressed to the Standard C++ timed primitives as `std::chrono::nanoseconds`.

This is an interface-resolution statement, not a guarantee that a host operating system or Standard Library scheduler will physically wake with one-nanosecond precision.

Interrupt-related properties are advertised as unsupported:

```text
CountingSemaphoreSupportsInterruptRelease = false
SignalSupportsInterruptNotification       = false
SpinLockSupportsInterruptContext          = false
```

Standard C++ defines no portable ISR/interrupt execution model, so this repository does not invent one.

## Mutex

`MutexProvider` wraps `std::timed_mutex`.

`Acquire()` maps the Platform timeout forms to:

```text
WaitForever -> lock()
NoWait      -> try_lock()
finite      -> try_lock_for(std::chrono::nanoseconds(...))
```

`RecursiveMutexProvider` uses the same timeout mapping over `std::recursive_timed_mutex`.

Both providers rely on the normal Standard C++ ownership preconditions for unlock. The provider does not add a separate ownership registry.

## ReadWriteMutex

`ReadWriteMutexProvider` wraps `std::shared_timed_mutex`.

Read acquisition uses:

```text
lock_shared
try_lock_shared
try_lock_shared_for
```

according to the requested wait policy.

Write acquisition uses the timed-mutex path:

```text
lock
try_lock
try_lock_for
```

The fairness policy of `std::shared_timed_mutex` is implementation-defined by the selected Standard Library/runtime; this provider does not claim writer preference or reader preference.

## CountingSemaphore

C++17 has no standard counting semaphore, so the provider implements the Platform contract from:

```text
std::mutex
std::condition_variable
fixed maximum/count state
```

`Initialize(maximum, initial)` rejects:

```text
re-initialization
maximum == 0
initial > maximum
```

`Acquire()` waits until a permit is available according to `WaitTimeout`, then decrements the count.

`Release()` increments the count only when below the configured maximum and wakes one eligible waiter. Releasing at maximum reports `CapacityReached` rather than overflowing.

`ReleaseFromInterrupt()` always reports `UnsupportedInterruptContext`.

## Signal

`SignalProvider` implements a latched/coalescing signal with:

```text
std::mutex
std::condition_variable
one Boolean latch
```

`Notify()` establishes the latched state and wakes one waiter.

Repeated notifications may coalesce while the latch is already set.

`Wait()` consumes the latch on success.

`NotifyFromInterrupt()` always reports `UnsupportedInterruptContext`.

## SpinLock

`SpinLockProvider` uses `std::atomic_flag`.

`Acquire()` repeatedly performs `test_and_set(std::memory_order_acquire)` and calls `std::this_thread::yield()` while another execution context owns the flag.

`Release()` clears the flag with `std::memory_order_release`.

The provider must only protect very short non-blocking critical regions. It must not be held across waits, blocking I/O, joins, or work that depends on another execution context making progress.

`AcquireFromInterrupt()` and `ReleaseFromInterrupt()` report `UnsupportedInterruptContext`.

## Failure behavior

The public methods are `noexcept` where required by the Platform contract.

Standard Library operations that may throw are caught inside the provider and mapped to the corresponding strongly typed `ProviderFailure` result where such a result exists.

Timeout, capacity exhaustion, initialization errors, unsupported interrupt operations, and provider failures remain semantically distinct.

Caller contract violations that are undefined behavior under the underlying Standard C++ synchronization primitive cannot be made reliably diagnosable by wrapping them. Callers must still obey the documented ownership and pairing rules.

## Resource and determinism boundary

The ESPressio provider objects own their Standard C++ synchronization objects directly and introduce no ESPressio registry, worker thread, or callback collection.

However, C++17 does not require the implementation internals of `std::mutex`, `std::condition_variable`, `std::shared_timed_mutex`, or related runtime facilities to be allocation-free or represented entirely inline.

Therefore this Portable backend does **not** claim the deterministic static native-resource guarantees provided by the FreeRTOS static providers. Its resource behavior beyond the visible provider members is implementation-defined by the selected Standard Library and host runtime.

Applications with strict native storage or embedded real-time requirements should select a concrete provider whose Composition/resource contract meets those requirements.

## Why ExecutionContext is absent

The Platform `ExecutionContext` contract requires caller-supplied native control and stack storage.

Portable `std::thread` does not expose a C++17 mechanism to provide and own those native storage regions. Implementing an `ExecutionContext` provider here would therefore weaken the abstraction contract.

The capability is intentionally not offered rather than pretending `std::thread` satisfies requirements it cannot portably satisfy.
