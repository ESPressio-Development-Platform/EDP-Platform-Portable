# src/synchronization/PortableSynchronizationProviders.hpp

**Primary classification:** PUBLIC PROVIDER / EXTENSION API

**Source baseline:** `ac8b4d22ad8030368db10750f751b2cdf1d58e18`

[Open exact source](https://github.com/ESPressio-Development-Platform/EDP-Platform-Portable/blob/ac8b4d22ad8030368db10750f751b2cdf1d58e18/src/synchronization/PortableSynchronizationProviders.hpp)

## Direct includes

- `atomic`
- `chrono`
- `condition_variable`
- `cstdint`
- `mutex`
- `shared_mutex`
- `thread`
- `ESPressio_Platform.hpp`

## Documented declarations

### `WaitResolutionNanoseconds`

**Classification:** PUBLIC PROVIDER / EXTENSION API

Portable wait resolution advertised to the Platform Composition.

```cpp
inline constexpr std::uint64_t WaitResolutionNanoseconds = 1U;
```

### `TTimedMutex`

**Classification:** PUBLIC PROVIDER / EXTENSION API

Performs timeout-aware acquisition against a Standard C++ timed mutex.

```cpp
template<class TTimedMutex>
        ESPressio::Platform::Synchronization::LockAcquireResult AcquireTimedMutex(
            TTimedMutex& mutex,
            ESPressio::Platform::Synchronization::WaitTimeout timeout
        ) noexcept
```

### `MutexProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API

Standard C++ timed-mutex provider.

```cpp
class MutexProvider final : public Framework::Provider<
        ESPressio::Platform::Domain,
```

### `_mutex`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Standard C++ timed mutex used by this provider.

```cpp
std::timed_mutex _mutex;
```

### `MutexProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Creates an unlocked portable mutex.

```cpp
MutexProvider() = default;
```

### `MutexProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents copying mutex state.

```cpp
MutexProvider(const MutexProvider&) = delete;
```

### `operator`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents copy assignment of mutex state.

```cpp
MutexProvider& operator =(const MutexProvider&) = delete;
```

### `MutexProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents moving mutex state.

```cpp
MutexProvider(MutexProvider&&) = delete;
```

### `operator`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents move assignment of mutex state.

```cpp
MutexProvider& operator =(MutexProvider&&) = delete;
```

### `Acquire`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Acquires the mutex according to the requested wait policy.

```cpp
ESPressio::Platform::Synchronization::LockAcquireResult Acquire(
                ESPressio::Platform::Synchronization::WaitTimeout timeout
            ) noexcept
```

### `Release`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Releases the mutex owned by the current execution context.

```cpp
ESPressio::Platform::Synchronization::LockReleaseResult Release() noexcept
```

### `RecursiveMutexProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API

Standard C++ recursive timed-mutex provider.

```cpp
class RecursiveMutexProvider final : public Framework::Provider<
        ESPressio::Platform::Domain,
```

### `_mutex`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Standard C++ recursive timed mutex used by this provider.

```cpp
std::recursive_timed_mutex _mutex;
```

### `RecursiveMutexProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Creates an unlocked recursive mutex.

```cpp
RecursiveMutexProvider() = default;
```

### `RecursiveMutexProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents copying mutex state.

```cpp
RecursiveMutexProvider(const RecursiveMutexProvider&) = delete;
```

### `operator`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents copy assignment of mutex state.

```cpp
RecursiveMutexProvider& operator =(const RecursiveMutexProvider&) = delete;
```

### `RecursiveMutexProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents moving mutex state.

```cpp
RecursiveMutexProvider(RecursiveMutexProvider&&) = delete;
```

### `operator`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents move assignment of mutex state.

```cpp
RecursiveMutexProvider& operator =(RecursiveMutexProvider&&) = delete;
```

### `Acquire`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Acquires the recursive mutex according to the requested wait policy.

```cpp
ESPressio::Platform::Synchronization::LockAcquireResult Acquire(
                ESPressio::Platform::Synchronization::WaitTimeout timeout
            ) noexcept
```

### `Release`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Releases one recursive acquisition owned by the current execution context.

```cpp
ESPressio::Platform::Synchronization::LockReleaseResult Release() noexcept
```

### `ReadWriteMutexProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API

Standard C++ shared timed-mutex provider.

```cpp
class ReadWriteMutexProvider final : public Framework::Provider<
        ESPressio::Platform::Domain,
```

### `_mutex`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Standard C++ shared timed mutex used by this provider.

```cpp
std::shared_timed_mutex _mutex;
```

### `ReadWriteMutexProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Creates an unlocked read/write mutex.

```cpp
ReadWriteMutexProvider() = default;
```

### `ReadWriteMutexProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents copying mutex state.

```cpp
ReadWriteMutexProvider(const ReadWriteMutexProvider&) = delete;
```

### `operator`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents copy assignment of mutex state.

```cpp
ReadWriteMutexProvider& operator =(const ReadWriteMutexProvider&) = delete;
```

### `ReadWriteMutexProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents moving mutex state.

```cpp
ReadWriteMutexProvider(ReadWriteMutexProvider&&) = delete;
```

### `operator`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents move assignment of mutex state.

```cpp
ReadWriteMutexProvider& operator =(ReadWriteMutexProvider&&) = delete;
```

### `AcquireRead`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Acquires a shared read lock according to the requested wait policy.

```cpp
ESPressio::Platform::Synchronization::LockAcquireResult AcquireRead(
                ESPressio::Platform::Synchronization::WaitTimeout timeout
            ) noexcept
```

### `ReleaseRead`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Releases one shared read lock.

```cpp
ESPressio::Platform::Synchronization::LockReleaseResult ReleaseRead() noexcept
```

### `AcquireWrite`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Acquires the exclusive write lock according to the requested wait policy.

```cpp
ESPressio::Platform::Synchronization::LockAcquireResult AcquireWrite(
                ESPressio::Platform::Synchronization::WaitTimeout timeout
            ) noexcept
```

### `ReleaseWrite`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Releases the exclusive write lock.

```cpp
ESPressio::Platform::Synchronization::LockReleaseResult ReleaseWrite() noexcept
```

### `CountingSemaphoreProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API

Standard C++ condition-variable-backed counting semaphore provider.

```cpp
class CountingSemaphoreProvider final : public Framework::Provider<
        ESPressio::Platform::Domain,
```

### `_mutex`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Mutex protecting semaphore counters.

```cpp
std::mutex _mutex;
```

### `_available`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Condition variable used to block permit waiters.

```cpp
std::condition_variable _available;
```

### `_maximum`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Maximum permit count.

```cpp
std::uint32_t _maximum = 0U;
```

### `_count`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Current available permit count.

```cpp
std::uint32_t _count = 0U;
```

### `_initialized`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Indicates whether the semaphore was initialized.

```cpp
bool _initialized = false;
```

### `CountingSemaphoreProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Creates an uninitialized counting semaphore.

```cpp
CountingSemaphoreProvider() = default;
```

### `CountingSemaphoreProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents copying semaphore state.

```cpp
CountingSemaphoreProvider(const CountingSemaphoreProvider&) = delete;
```

### `operator`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents copy assignment of semaphore state.

```cpp
CountingSemaphoreProvider& operator =(const CountingSemaphoreProvider&) = delete;
```

### `CountingSemaphoreProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents moving semaphore state.

```cpp
CountingSemaphoreProvider(CountingSemaphoreProvider&&) = delete;
```

### `operator`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents move assignment of semaphore state.

```cpp
CountingSemaphoreProvider& operator =(CountingSemaphoreProvider&&) = delete;
```

### `Initialize`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Initializes the semaphore with fixed maximum and initial counts.

```cpp
ESPressio::Platform::Synchronization::SemaphoreInitializationResult Initialize(
                std::uint32_t maximum,
                std::uint32_t initial
            ) noexcept
```

### `Acquire`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Acquires one permit according to the requested wait policy.

```cpp
ESPressio::Platform::Synchronization::SemaphoreAcquireResult Acquire(
                ESPressio::Platform::Synchronization::WaitTimeout timeout
            ) noexcept
```

### `Release`

**Classification:** PUBLIC PROVIDER / EXTENSION API

Releases one permit and wakes one eligible waiter.

```cpp
ESPressio::Platform::Synchronization::SemaphoreReleaseResult Release() noexcept
```

### `ReleaseFromInterrupt`

**Classification:** PUBLIC PROVIDER / EXTENSION API

Reports that Standard C++ cannot provide an interrupt-context release contract.

```cpp
ESPressio::Platform::Synchronization::SemaphoreReleaseResult ReleaseFromInterrupt() noexcept
```

### `SignalProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API

Standard C++ condition-variable-backed latched signal provider.

```cpp
class SignalProvider final : public Framework::Provider<
        ESPressio::Platform::Domain,
```

### `_mutex`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Mutex protecting the signal latch.

```cpp
std::mutex _mutex;
```

### `_condition`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Condition variable used to wake one waiter.

```cpp
std::condition_variable _condition;
```

### `_signaled`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Latched signal state.

```cpp
bool _signaled = false;
```

### `SignalProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Creates an unsignaled portable signal.

```cpp
SignalProvider() = default;
```

### `SignalProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents copying signal state.

```cpp
SignalProvider(const SignalProvider&) = delete;
```

### `operator`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents copy assignment of signal state.

```cpp
SignalProvider& operator =(const SignalProvider&) = delete;
```

### `SignalProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents moving signal state.

```cpp
SignalProvider(SignalProvider&&) = delete;
```

### `operator`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents move assignment of signal state.

```cpp
SignalProvider& operator =(SignalProvider&&) = delete;
```

### `Notify`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Latches the signal and wakes one waiter.

```cpp
ESPressio::Platform::Synchronization::SignalNotifyResult Notify() noexcept
```

### `NotifyFromInterrupt`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Reports that Standard C++ cannot provide an interrupt-context notification contract.

```cpp
ESPressio::Platform::Synchronization::SignalNotifyResult NotifyFromInterrupt() noexcept
```

### `Wait`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Waits for and consumes the current signal latch.

```cpp
ESPressio::Platform::Synchronization::SignalWaitResult Wait(
                ESPressio::Platform::Synchronization::WaitTimeout timeout
            ) noexcept
```

### `SpinLockProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API

Standard C++ atomic-flag spin-lock provider.

```cpp
class SpinLockProvider final : public Framework::Provider<
        ESPressio::Platform::Domain,
```

### `_flag`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Atomic ownership flag.

```cpp
std::atomic_flag _flag = ATOMIC_FLAG_INIT;
```

### `SpinLockProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Creates an unlocked spin lock.

```cpp
SpinLockProvider() noexcept = default;
```

### `SpinLockProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents copying spin-lock state.

```cpp
SpinLockProvider(const SpinLockProvider&) = delete;
```

### `operator`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents copy assignment of spin-lock state.

```cpp
SpinLockProvider& operator =(const SpinLockProvider&) = delete;
```

### `SpinLockProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents moving spin-lock state.

```cpp
SpinLockProvider(SpinLockProvider&&) = delete;
```

### `operator`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents move assignment of spin-lock state.

```cpp
SpinLockProvider& operator =(SpinLockProvider&&) = delete;
```

### `Acquire`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Spins until the lock is acquired.

```cpp
void Acquire() noexcept
```

### `Release`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Releases the spin lock.

```cpp
ESPressio::Platform::Synchronization::SpinLockReleaseResult Release() noexcept
```

### `AcquireFromInterrupt`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Reports that Standard C++ has no portable interrupt-context acquisition contract.

```cpp
ESPressio::Platform::Synchronization::SpinLockAcquireResult AcquireFromInterrupt() noexcept
```

### `ReleaseFromInterrupt`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Reports that Standard C++ has no portable interrupt-context release contract.

```cpp
ESPressio::Platform::Synchronization::SpinLockReleaseResult ReleaseFromInterrupt() noexcept
```

### `MutexContract`

**Classification:** PUBLIC PROVIDER / EXTENSION API

Compile-time validation of the portable Mutex provider.

```cpp
using MutexContract = ESPressio::Platform::Synchronization::Detail::MutexProviderTraits<MutexProvider>;
```

### `RecursiveMutexContract`

**Classification:** PUBLIC PROVIDER / EXTENSION API

Compile-time validation of the portable RecursiveMutex provider.

```cpp
using RecursiveMutexContract = ESPressio::Platform::Synchronization::Detail::RecursiveMutexProviderTraits<RecursiveMutexProvider>;
```

### `ReadWriteMutexContract`

**Classification:** PUBLIC PROVIDER / EXTENSION API

Compile-time validation of the portable ReadWriteMutex provider.

```cpp
using ReadWriteMutexContract = ESPressio::Platform::Synchronization::Detail::ReadWriteMutexProviderTraits<ReadWriteMutexProvider>;
```

### `CountingSemaphoreContract`

**Classification:** PUBLIC PROVIDER / EXTENSION API

Compile-time validation of the portable CountingSemaphore provider.

```cpp
using CountingSemaphoreContract = ESPressio::Platform::Synchronization::Detail::CountingSemaphoreProviderTraits<CountingSemaphoreProvider>;
```

### `SignalContract`

**Classification:** PUBLIC PROVIDER / EXTENSION API

Compile-time validation of the portable Signal provider.

```cpp
using SignalContract = ESPressio::Platform::Synchronization::Detail::SignalProviderTraits<SignalProvider>;
```

### `SpinLockContract`

**Classification:** PUBLIC PROVIDER / EXTENSION API

Compile-time validation of the portable SpinLock provider.

```cpp
using SpinLockContract = ESPressio::Platform::Synchronization::Detail::SpinLockProviderTraits<SpinLockProvider>;
```

