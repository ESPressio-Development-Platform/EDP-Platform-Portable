#include <cstdint>

#include "TestRequire.hpp"

#include <ESPressio_Platform_Portable.hpp>

/// Verifies the Standard C++ providers against their Platform contracts and basic runtime behavior.
int main() {
    using namespace ESPressio::Platform;

    Portable::Concurrency::AtomicWord32Provider::Word word;
    word.StoreRelease(
        42U
    );

    EDP_PORTABLE_TEST_REQUIRE(
        word.LoadAcquire() == 42U
    );

    Portable::Synchronization::MutexProvider mutex;

    EDP_PORTABLE_TEST_REQUIRE(
        mutex.Acquire(
            Synchronization::WaitTimeout::NoWait()
        ) == Synchronization::LockAcquireResult::Acquired
    );

    EDP_PORTABLE_TEST_REQUIRE(
        mutex.Release() ==
        Synchronization::LockReleaseResult::Released
    );

    Portable::Synchronization::RecursiveMutexProvider recursiveMutex;

    EDP_PORTABLE_TEST_REQUIRE(
        recursiveMutex.Acquire(
            Synchronization::WaitTimeout::NoWait()
        ) == Synchronization::LockAcquireResult::Acquired
    );

    EDP_PORTABLE_TEST_REQUIRE(
        recursiveMutex.Acquire(
            Synchronization::WaitTimeout::NoWait()
        ) == Synchronization::LockAcquireResult::Acquired
    );

    EDP_PORTABLE_TEST_REQUIRE(
        recursiveMutex.Release() ==
        Synchronization::LockReleaseResult::Released
    );

    EDP_PORTABLE_TEST_REQUIRE(
        recursiveMutex.Release() ==
        Synchronization::LockReleaseResult::Released
    );

    Portable::Synchronization::ReadWriteMutexProvider readWriteMutex;

    EDP_PORTABLE_TEST_REQUIRE(
        readWriteMutex.AcquireRead(
            Synchronization::WaitTimeout::NoWait()
        ) == Synchronization::LockAcquireResult::Acquired
    );

    EDP_PORTABLE_TEST_REQUIRE(
        readWriteMutex.ReleaseRead() ==
        Synchronization::LockReleaseResult::Released
    );

    EDP_PORTABLE_TEST_REQUIRE(
        readWriteMutex.AcquireWrite(
            Synchronization::WaitTimeout::NoWait()
        ) == Synchronization::LockAcquireResult::Acquired
    );

    EDP_PORTABLE_TEST_REQUIRE(
        readWriteMutex.ReleaseWrite() ==
        Synchronization::LockReleaseResult::Released
    );

    Portable::Synchronization::CountingSemaphoreProvider semaphore;

    EDP_PORTABLE_TEST_REQUIRE(
        semaphore.Initialize(
            2U,
            1U
        ) == Synchronization::SemaphoreInitializationResult::Succeeded
    );

    EDP_PORTABLE_TEST_REQUIRE(
        semaphore.Acquire(
            Synchronization::WaitTimeout::NoWait()
        ) == Synchronization::SemaphoreAcquireResult::Acquired
    );

    EDP_PORTABLE_TEST_REQUIRE(
        semaphore.Acquire(
            Synchronization::WaitTimeout::NoWait()
        ) == Synchronization::SemaphoreAcquireResult::TimedOut
    );

    EDP_PORTABLE_TEST_REQUIRE(
        semaphore.Release() ==
        Synchronization::SemaphoreReleaseResult::Released
    );

    EDP_PORTABLE_TEST_REQUIRE(
        semaphore.ReleaseFromInterrupt() ==
        Synchronization::SemaphoreReleaseResult::UnsupportedInterruptContext
    );

    Portable::Synchronization::SignalProvider signal;

    EDP_PORTABLE_TEST_REQUIRE(
        signal.Notify() ==
        Synchronization::SignalNotifyResult::Signaled
    );

    EDP_PORTABLE_TEST_REQUIRE(
        signal.Notify() ==
        Synchronization::SignalNotifyResult::Signaled
    );

    EDP_PORTABLE_TEST_REQUIRE(
        signal.Wait(
            Synchronization::WaitTimeout::NoWait()
        ) == Synchronization::SignalWaitResult::Signaled
    );

    EDP_PORTABLE_TEST_REQUIRE(
        signal.Wait(
            Synchronization::WaitTimeout::NoWait()
        ) == Synchronization::SignalWaitResult::TimedOut
    );

    Portable::Synchronization::SpinLockProvider spinLock;
    spinLock.Acquire();

    EDP_PORTABLE_TEST_REQUIRE(
        spinLock.Release() ==
        Synchronization::SpinLockReleaseResult::Released
    );

    EDP_PORTABLE_TEST_REQUIRE(
        spinLock.AcquireFromInterrupt() ==
        Synchronization::SpinLockAcquireResult::UnsupportedInterruptContext
    );

    return 0;
}
