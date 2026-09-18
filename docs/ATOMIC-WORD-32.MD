# Portable AtomicWord32 Provider

## Purpose and scope

`EDP-Platform-Portable` supplies the Standard C++ concrete provider for the `EDP-Platform` `AtomicWord32` capability.

The provider exists so Platform-neutral algorithms such as `ConcurrentSnapshot` can consume the required four-byte lock-free atomic operations without embedding `std::atomic` into the abstraction repository.

## Composition contract

The provider offers:

```text
ESPressio::Platform::Concurrency::AtomicWord32
```

with:

```text
LockFree               = true
AtomicWordStorageBytes = 4
```

The repository enforces those claims at compile time with `static_assert` checks requiring:

```text
std::atomic<std::uint32_t>::is_always_lock_free
sizeof(std::atomic<std::uint32_t>) == sizeof(std::uint32_t)
```

If a Standard C++ implementation cannot satisfy those invariants, this provider is intentionally unavailable through compilation failure rather than silently falling back to a lock.

## Runtime representation

`AtomicWord32Provider` exposes the nested `Word` Type required by the Platform contract.

Each `Word` owns exactly one inline:

```cpp
std::atomic<std::uint32_t>
```

initialized to zero.

`Word` is non-copyable and non-movable so its synchronization storage remains address-stable.

## Memory-order surface

The provider exposes only the ordering operations required by the Platform abstraction:

```text
LoadRelaxed            -> std::memory_order_relaxed
LoadAcquire            -> std::memory_order_acquire
StoreRelaxed           -> std::memory_order_relaxed
StoreRelease           -> std::memory_order_release
CompareExchangeAcqRel  -> success: acq_rel, failure: acquire
```

The complete Standard C++ memory-order vocabulary is deliberately not leaked into higher ESPressio domains.

## Resource behavior

The atomic word is fixed inline storage. The provider introduces:

```text
no heap allocation
no worker thread
no registry
no callback collection
no mutex fallback
```

The lock-free and four-byte storage guarantees are part of the compile-time provider contract rather than runtime observations.

## Thread and interrupt boundary

The provider supplies the atomic semantics required by the Platform concurrency contract for ordinary C++ concurrent execution.

`AtomicWord32` currently has no separate Platform property claiming ISR/interrupt-context support. Consumers must not infer an interrupt contract merely because a particular compiler or target happens to implement lock-free atomics in a way that also works inside an ISR.

## Integration

`EDP-Platform` owns `ConcurrentSnapshot`; this repository supplies only the concrete atomic word used by that Platform-neutral algorithm.

Application Composition selects `AtomicWord32Provider` where this Standard C++ implementation satisfies the target/toolchain contract.
