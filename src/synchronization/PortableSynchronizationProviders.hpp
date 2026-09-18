#pragma once

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <mutex>
#include <shared_mutex>
#include <thread>

#include <ESPressio_Platform.hpp>

namespace ESPressio::Platform::Portable::Synchronization {

    namespace Framework = ESPressio::System::CompositionFramework;

    namespace Detail {

        /// Portable wait resolution advertised to the Platform Composition.
        inline constexpr std::uint64_t WaitResolutionNanoseconds = 1U;


        /// Performs timeout-aware acquisition against a Standard C++ timed mutex.
        template<class TTimedMutex>
        ESPressio::Platform::Synchronization::LockAcquireResult AcquireTimedMutex(
            TTimedMutex& mutex,
            ESPressio::Platform::Synchronization::WaitTimeout timeout
        ) noexcept {
            try {
                if (timeout.IsForever()) {
                    mutex.lock();
                    return ESPressio::Platform::Synchronization::LockAcquireResult::Acquired;
                }

                if (timeout.IsNoWait()) {
                    return mutex.try_lock()
                        ? ESPressio::Platform::Synchronization::LockAcquireResult::Acquired
                        : ESPressio::Platform::Synchronization::LockAcquireResult::TimedOut;
                }

                return mutex.try_lock_for(
                    std::chrono::nanoseconds(
                        timeout.Nanoseconds()
                    )
                )
                    ? ESPressio::Platform::Synchronization::LockAcquireResult::Acquired
                    : ESPressio::Platform::Synchronization::LockAcquireResult::TimedOut;
            } catch (...) {
                return ESPressio::Platform::Synchronization::LockAcquireResult::ProviderFailure;
            }
        }

    } // ESPressio::Platform::Portable::Synchronization::Detail


    /// Standard C++ timed-mutex provider.
    class MutexProvider final : public Framework::Provider<
        ESPressio::Platform::Domain,
        Framework::Provides<
            Framework::Offer<
                ESPressio::Platform::Synchronization::Mutex,
                Framework::PropertyValue<
                    ESPressio::Platform::Synchronization::MutexWaitResolutionNanoseconds,
                    Detail::WaitResolutionNanoseconds
                >
            >
        >
    > {

        private:

            // Native synchronization state.

            /// Standard C++ timed mutex used by this provider.
            std::timed_mutex _mutex;

        public:

            // Construction and lifetime.

            /// Creates an unlocked portable mutex.
            MutexProvider() = default;

            /// Prevents copying mutex state.
            MutexProvider(const MutexProvider&) = delete;

            /// Prevents copy assignment of mutex state.
            MutexProvider& operator =(const MutexProvider&) = delete;

            /// Prevents moving mutex state.
            MutexProvider(MutexProvider&&) = delete;

            /// Prevents move assignment of mutex state.
            MutexProvider& operator =(MutexProvider&&) = delete;


            // Lock operations.

            /// Acquires the mutex according to the requested wait policy.
            ESPressio::Platform::Synchronization::LockAcquireResult Acquire(
                ESPressio::Platform::Synchronization::WaitTimeout timeout
            ) noexcept {
                return Detail::AcquireTimedMutex(
                    _mutex,
                    timeout
                );
            }

            /// Releases the mutex owned by the current execution context.
            ESPressio::Platform::Synchronization::LockReleaseResult Release() noexcept {
                try {
                    _mutex.unlock();
                    return ESPressio::Platform::Synchronization::LockReleaseResult::Released;
                } catch (...) {
                    return ESPressio::Platform::Synchronization::LockReleaseResult::ProviderFailure;
                }
            }

    };


    /// Standard C++ recursive timed-mutex provider.
    class RecursiveMutexProvider final : public Framework::Provider<
        ESPressio::Platform::Domain,
        Framework::Provides<
            Framework::Offer<
                ESPressio::Platform::Synchronization::RecursiveMutex,
                Framework::PropertyValue<
                    ESPressio::Platform::Synchronization::RecursiveMutexWaitResolutionNanoseconds,
                    Detail::WaitResolutionNanoseconds
                >
            >
        >
    > {

        private:

            // Native synchronization state.

            /// Standard C++ recursive timed mutex used by this provider.
            std::recursive_timed_mutex _mutex;

        public:

            // Construction and lifetime.

            /// Creates an unlocked recursive mutex.
            RecursiveMutexProvider() = default;

            /// Prevents copying mutex state.
            RecursiveMutexProvider(const RecursiveMutexProvider&) = delete;

            /// Prevents copy assignment of mutex state.
            RecursiveMutexProvider& operator =(const RecursiveMutexProvider&) = delete;

            /// Prevents moving mutex state.
            RecursiveMutexProvider(RecursiveMutexProvider&&) = delete;

            /// Prevents move assignment of mutex state.
            RecursiveMutexProvider& operator =(RecursiveMutexProvider&&) = delete;


            // Lock operations.

            /// Acquires the recursive mutex according to the requested wait policy.
            ESPressio::Platform::Synchronization::LockAcquireResult Acquire(
                ESPressio::Platform::Synchronization::WaitTimeout timeout
            ) noexcept {
                return Detail::AcquireTimedMutex(
                    _mutex,
                    timeout
                );
            }

            /// Releases one recursive acquisition owned by the current execution context.
            ESPressio::Platform::Synchronization::LockReleaseResult Release() noexcept {
                try {
                    _mutex.unlock();
                    return ESPressio::Platform::Synchronization::LockReleaseResult::Released;
                } catch (...) {
                    return ESPressio::Platform::Synchronization::LockReleaseResult::ProviderFailure;
                }
            }

    };


    /// Standard C++ shared timed-mutex provider.
    class ReadWriteMutexProvider final : public Framework::Provider<
        ESPressio::Platform::Domain,
        Framework::Provides<
            Framework::Offer<
                ESPressio::Platform::Synchronization::ReadWriteMutex,
                Framework::PropertyValue<
                    ESPressio::Platform::Synchronization::ReadWriteMutexWaitResolutionNanoseconds,
                    Detail::WaitResolutionNanoseconds
                >
            >
        >
    > {

        private:

            // Native synchronization state.

            /// Standard C++ shared timed mutex used by this provider.
            std::shared_timed_mutex _mutex;

        public:

            // Construction and lifetime.

            /// Creates an unlocked read/write mutex.
            ReadWriteMutexProvider() = default;

            /// Prevents copying mutex state.
            ReadWriteMutexProvider(const ReadWriteMutexProvider&) = delete;

            /// Prevents copy assignment of mutex state.
            ReadWriteMutexProvider& operator =(const ReadWriteMutexProvider&) = delete;

            /// Prevents moving mutex state.
            ReadWriteMutexProvider(ReadWriteMutexProvider&&) = delete;

            /// Prevents move assignment of mutex state.
            ReadWriteMutexProvider& operator =(ReadWriteMutexProvider&&) = delete;


            // Shared-read operations.

            /// Acquires a shared read lock according to the requested wait policy.
            ESPressio::Platform::Synchronization::LockAcquireResult AcquireRead(
                ESPressio::Platform::Synchronization::WaitTimeout timeout
            ) noexcept {
                try {
                    if (timeout.IsForever()) {
                        _mutex.lock_shared();
                        return ESPressio::Platform::Synchronization::LockAcquireResult::Acquired;
                    }

                    if (timeout.IsNoWait()) {
                        return _mutex.try_lock_shared()
                            ? ESPressio::Platform::Synchronization::LockAcquireResult::Acquired
                            : ESPressio::Platform::Synchronization::LockAcquireResult::TimedOut;
                    }

                    return _mutex.try_lock_shared_for(
                        std::chrono::nanoseconds(
                            timeout.Nanoseconds()
                        )
                    )
                        ? ESPressio::Platform::Synchronization::LockAcquireResult::Acquired
                        : ESPressio::Platform::Synchronization::LockAcquireResult::TimedOut;
                } catch (...) {
                    return ESPressio::Platform::Synchronization::LockAcquireResult::ProviderFailure;
                }
            }

            /// Releases one shared read lock.
            ESPressio::Platform::Synchronization::LockReleaseResult ReleaseRead() noexcept {
                try {
                    _mutex.unlock_shared();
                    return ESPressio::Platform::Synchronization::LockReleaseResult::Released;
                } catch (...) {
                    return ESPressio::Platform::Synchronization::LockReleaseResult::ProviderFailure;
                }
            }


            // Exclusive-write operations.

            /// Acquires the exclusive write lock according to the requested wait policy.
            ESPressio::Platform::Synchronization::LockAcquireResult AcquireWrite(
                ESPressio::Platform::Synchronization::WaitTimeout timeout
            ) noexcept {
                return Detail::AcquireTimedMutex(
                    _mutex,
                    timeout
                );
            }

            /// Releases the exclusive write lock.
            ESPressio::Platform::Synchronization::LockReleaseResult ReleaseWrite() noexcept {
                try {
                    _mutex.unlock();
                    return ESPressio::Platform::Synchronization::LockReleaseResult::Released;
                } catch (...) {
                    return ESPressio::Platform::Synchronization::LockReleaseResult::ProviderFailure;
                }
            }

    };


    /// Standard C++ condition-variable-backed counting semaphore provider.
    class CountingSemaphoreProvider final : public Framework::Provider<
        ESPressio::Platform::Domain,
        Framework::Provides<
            Framework::Offer<
                ESPressio::Platform::Synchronization::CountingSemaphore,
                Framework::PropertyValue<
                    ESPressio::Platform::Synchronization::CountingSemaphoreWaitResolutionNanoseconds,
                    Detail::WaitResolutionNanoseconds
                >,
                Framework::PropertyValue<
                    ESPressio::Platform::Synchronization::CountingSemaphoreSupportsInterruptRelease,
                    false
                >
            >
        >
    > {

        private:

            // Synchronization state.

            /// Mutex protecting semaphore counters.
            std::mutex _mutex;

            /// Condition variable used to block permit waiters.
            std::condition_variable _available;

            /// Maximum permit count.
            std::uint32_t _maximum = 0U;

            /// Current available permit count.
            std::uint32_t _count = 0U;

            /// Indicates whether the semaphore was initialized.
            bool _initialized = false;

        public:

            // Construction and lifetime.

            /// Creates an uninitialized counting semaphore.
            CountingSemaphoreProvider() = default;

            /// Prevents copying semaphore state.
            CountingSemaphoreProvider(const CountingSemaphoreProvider&) = delete;

            /// Prevents copy assignment of semaphore state.
            CountingSemaphoreProvider& operator =(const CountingSemaphoreProvider&) = delete;

            /// Prevents moving semaphore state.
            CountingSemaphoreProvider(CountingSemaphoreProvider&&) = delete;

            /// Prevents move assignment of semaphore state.
            CountingSemaphoreProvider& operator =(CountingSemaphoreProvider&&) = delete;


            // Initialization.

            /// Initializes the semaphore with fixed maximum and initial counts.
            ESPressio::Platform::Synchronization::SemaphoreInitializationResult Initialize(
                std::uint32_t maximum,
                std::uint32_t initial
            ) noexcept {
                std::lock_guard<std::mutex> lock(_mutex);

                if (_initialized) {
                    return ESPressio::Platform::Synchronization::SemaphoreInitializationResult::AlreadyInitialized;
                }

                if (maximum == 0U) {
                    return ESPressio::Platform::Synchronization::SemaphoreInitializationResult::InvalidMaximumCount;
                }

                if (initial > maximum) {
                    return ESPressio::Platform::Synchronization::SemaphoreInitializationResult::InvalidInitialCount;
                }

                _maximum = maximum;
                _count = initial;
                _initialized = true;

                return ESPressio::Platform::Synchronization::SemaphoreInitializationResult::Succeeded;
            }


            // Permit operations.

            /// Acquires one permit according to the requested wait policy.
            ESPressio::Platform::Synchronization::SemaphoreAcquireResult Acquire(
                ESPressio::Platform::Synchronization::WaitTimeout timeout
            ) noexcept {
                try {
                    std::unique_lock<std::mutex> lock(_mutex);

                    if (!_initialized) {
                        return ESPressio::Platform::Synchronization::SemaphoreAcquireResult::NotInitialized;
                    }

                    const auto available = [this]() noexcept {
                        return _count > 0U;
                    };

                    bool acquired = false;

                    if (timeout.IsForever()) {
                        _available.wait(
                            lock,
                            available
                        );
                        acquired = true;
                    } else if (timeout.IsNoWait()) {
                        acquired = available();
                    } else {
                        acquired = _available.wait_for(
                            lock,
                            std::chrono::nanoseconds(
                                timeout.Nanoseconds()
                            ),
                            available
                        );
                    }

                    if (!acquired) {
                        return ESPressio::Platform::Synchronization::SemaphoreAcquireResult::TimedOut;
                    }

                    --_count;
                    return ESPressio::Platform::Synchronization::SemaphoreAcquireResult::Acquired;
                } catch (...) {
                    return ESPressio::Platform::Synchronization::SemaphoreAcquireResult::ProviderFailure;
                }
            }

            /// Releases one permit and wakes one eligible waiter.
            ESPressio::Platform::Synchronization::SemaphoreReleaseResult Release() noexcept {
                try {
                    {
                        std::lock_guard<std::mutex> lock(_mutex);

                        if (!_initialized) {
                            return ESPressio::Platform::Synchronization::SemaphoreReleaseResult::NotInitialized;
                        }

                        if (_count >= _maximum) {
                            return ESPressio::Platform::Synchronization::SemaphoreReleaseResult::CapacityReached;
                        }

                        ++_count;
                    }

                    _available.notify_one();
                    return ESPressio::Platform::Synchronization::SemaphoreReleaseResult::Released;
                } catch (...) {
                    return ESPressio::Platform::Synchronization::SemaphoreReleaseResult::ProviderFailure;
                }
            }

            /// Reports that Standard C++ cannot provide an interrupt-context release contract.
            ESPressio::Platform::Synchronization::SemaphoreReleaseResult ReleaseFromInterrupt() noexcept {
                return ESPressio::Platform::Synchronization::SemaphoreReleaseResult::UnsupportedInterruptContext;
            }

    };


    /// Standard C++ condition-variable-backed latched signal provider.
    class SignalProvider final : public Framework::Provider<
        ESPressio::Platform::Domain,
        Framework::Provides<
            Framework::Offer<
                ESPressio::Platform::Synchronization::Signal,
                Framework::PropertyValue<
                    ESPressio::Platform::Synchronization::SignalWaitResolutionNanoseconds,
                    Detail::WaitResolutionNanoseconds
                >,
                Framework::PropertyValue<
                    ESPressio::Platform::Synchronization::SignalSupportsInterruptNotification,
                    false
                >
            >
        >
    > {

        private:

            // Signal state.

            /// Mutex protecting the signal latch.
            std::mutex _mutex;

            /// Condition variable used to wake one waiter.
            std::condition_variable _condition;

            /// Latched signal state.
            bool _signaled = false;

        public:

            // Construction and lifetime.

            /// Creates an unsignaled portable signal.
            SignalProvider() = default;

            /// Prevents copying signal state.
            SignalProvider(const SignalProvider&) = delete;

            /// Prevents copy assignment of signal state.
            SignalProvider& operator =(const SignalProvider&) = delete;

            /// Prevents moving signal state.
            SignalProvider(SignalProvider&&) = delete;

            /// Prevents move assignment of signal state.
            SignalProvider& operator =(SignalProvider&&) = delete;


            // Notification.

            /// Latches the signal and wakes one waiter.
            ESPressio::Platform::Synchronization::SignalNotifyResult Notify() noexcept {
                try {
                    {
                        std::lock_guard<std::mutex> lock(_mutex);
                        _signaled = true;
                    }

                    _condition.notify_one();
                    return ESPressio::Platform::Synchronization::SignalNotifyResult::Signaled;
                } catch (...) {
                    return ESPressio::Platform::Synchronization::SignalNotifyResult::ProviderFailure;
                }
            }

            /// Reports that Standard C++ cannot provide an interrupt-context notification contract.
            ESPressio::Platform::Synchronization::SignalNotifyResult NotifyFromInterrupt() noexcept {
                return ESPressio::Platform::Synchronization::SignalNotifyResult::UnsupportedInterruptContext;
            }


            // Waiting.

            /// Waits for and consumes the current signal latch.
            ESPressio::Platform::Synchronization::SignalWaitResult Wait(
                ESPressio::Platform::Synchronization::WaitTimeout timeout
            ) noexcept {
                try {
                    std::unique_lock<std::mutex> lock(_mutex);

                    const auto signaled = [this]() noexcept {
                        return _signaled;
                    };

                    bool received = false;

                    if (timeout.IsForever()) {
                        _condition.wait(
                            lock,
                            signaled
                        );
                        received = true;
                    } else if (timeout.IsNoWait()) {
                        received = signaled();
                    } else {
                        received = _condition.wait_for(
                            lock,
                            std::chrono::nanoseconds(
                                timeout.Nanoseconds()
                            ),
                            signaled
                        );
                    }

                    if (!received) {
                        return ESPressio::Platform::Synchronization::SignalWaitResult::TimedOut;
                    }

                    _signaled = false;
                    return ESPressio::Platform::Synchronization::SignalWaitResult::Signaled;
                } catch (...) {
                    return ESPressio::Platform::Synchronization::SignalWaitResult::ProviderFailure;
                }
            }

    };


    /// Standard C++ atomic-flag spin-lock provider.
    class SpinLockProvider final : public Framework::Provider<
        ESPressio::Platform::Domain,
        Framework::Provides<
            Framework::Offer<
                ESPressio::Platform::Synchronization::SpinLock,
                Framework::PropertyValue<
                    ESPressio::Platform::Synchronization::SpinLockSupportsInterruptContext,
                    false
                >
            >
        >
    > {

        private:

            // Spin-lock state.

            /// Atomic ownership flag.
            std::atomic_flag _flag = ATOMIC_FLAG_INIT;

        public:

            // Construction and lifetime.

            /// Creates an unlocked spin lock.
            SpinLockProvider() noexcept = default;

            /// Prevents copying spin-lock state.
            SpinLockProvider(const SpinLockProvider&) = delete;

            /// Prevents copy assignment of spin-lock state.
            SpinLockProvider& operator =(const SpinLockProvider&) = delete;

            /// Prevents moving spin-lock state.
            SpinLockProvider(SpinLockProvider&&) = delete;

            /// Prevents move assignment of spin-lock state.
            SpinLockProvider& operator =(SpinLockProvider&&) = delete;


            // Ordinary-context lock operations.

            /// Spins until the lock is acquired.
            void Acquire() noexcept {
                while (_flag.test_and_set(
                    std::memory_order_acquire
                )) {
                    std::this_thread::yield();
                }
            }

            /// Attempts one immediate lock acquisition.
            ESPressio::Platform::Synchronization::SpinLockTryAcquireResult TryAcquire() noexcept {
                return _flag.test_and_set(
                    std::memory_order_acquire
                )
                    ? ESPressio::Platform::Synchronization::SpinLockTryAcquireResult::Busy
                    : ESPressio::Platform::Synchronization::SpinLockTryAcquireResult::Acquired;
            }

            /// Releases the spin lock.
            ESPressio::Platform::Synchronization::SpinLockReleaseResult Release() noexcept {
                _flag.clear(
                    std::memory_order_release
                );

                return ESPressio::Platform::Synchronization::SpinLockReleaseResult::Released;
            }


            // Interrupt-context operations.

            /// Reports that Standard C++ has no portable interrupt-context acquisition contract.
            ESPressio::Platform::Synchronization::SpinLockTryAcquireResult TryAcquireFromInterrupt() noexcept {
                return ESPressio::Platform::Synchronization::SpinLockTryAcquireResult::UnsupportedInterruptContext;
            }

            /// Reports that Standard C++ has no portable interrupt-context release contract.
            ESPressio::Platform::Synchronization::SpinLockReleaseResult ReleaseFromInterrupt() noexcept {
                return ESPressio::Platform::Synchronization::SpinLockReleaseResult::UnsupportedInterruptContext;
            }

    };


    /// Compile-time validation of the portable Mutex provider.
    using MutexContract = ESPressio::Platform::Synchronization::Detail::MutexProviderTraits<MutexProvider>;

    /// Compile-time validation of the portable RecursiveMutex provider.
    using RecursiveMutexContract = ESPressio::Platform::Synchronization::Detail::RecursiveMutexProviderTraits<RecursiveMutexProvider>;

    /// Compile-time validation of the portable ReadWriteMutex provider.
    using ReadWriteMutexContract = ESPressio::Platform::Synchronization::Detail::ReadWriteMutexProviderTraits<ReadWriteMutexProvider>;

    /// Compile-time validation of the portable CountingSemaphore provider.
    using CountingSemaphoreContract = ESPressio::Platform::Synchronization::Detail::CountingSemaphoreProviderTraits<CountingSemaphoreProvider>;

    /// Compile-time validation of the portable Signal provider.
    using SignalContract = ESPressio::Platform::Synchronization::Detail::SignalProviderTraits<SignalProvider>;

    /// Compile-time validation of the portable SpinLock provider.
    using SpinLockContract = ESPressio::Platform::Synchronization::Detail::SpinLockProviderTraits<SpinLockProvider>;

} // ESPressio::Platform::Portable::Synchronization
