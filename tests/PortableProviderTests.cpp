#include <cassert>
#include <cstdint>

#include <ESPressio_Platform_Portable.hpp>

/// Verifies the Standard C++ providers against their Platform contracts and basic runtime behavior.
int main() {
    using namespace ESPressio::Platform;

    Portable::Concurrency::AtomicWord32Provider::Word word;
    word.StoreRelease(
        42U
    );

    assert(
        word.LoadAcquire() == 42U
    );

    Portable::Synchronization::MutexProvider mutex;

    assert(
        mutex.Acquire(
            Synchronization::WaitTimeout::NoWait()
        ) == Synchronization::LockAcquireResult::Acquired
    );

    assert(
        mutex.Release() ==
        Synchronization::LockReleaseResult::Released
    );

    Portable::Synchronization::RecursiveMutexProvider recursiveMutex;

    assert(
        recursiveMutex.Acquire(
            Synchronization::WaitTimeout::NoWait()
        ) == Synchronization::LockAcquireResult::Acquired
    );

    assert(
        recursiveMutex.Acquire(
            Synchronization::WaitTimeout::NoWait()
        ) == Synchronization::LockAcquireResult::Acquired
    );

    assert(
        recursiveMutex.Release() ==
        Synchronization::LockReleaseResult::Released
    );

    assert(
        recursiveMutex.Release() ==
        Synchronization::LockReleaseResult::Released
    );

    Portable::Synchronization::ReadWriteMutexProvider readWriteMutex;

    assert(
        readWriteMutex.AcquireRead(
            Synchronization::WaitTimeout::NoWait()
        ) == Synchronization::LockAcquireResult::Acquired
    );

    assert(
        readWriteMutex.ReleaseRead() ==
        Synchronization::LockReleaseResult::Released
    );

    assert(
        readWriteMutex.AcquireWrite(
            Synchronization::WaitTimeout::NoWait()
        ) == Synchronization::LockAcquireResult::Acquired
    );

    assert(
        readWriteMutex.ReleaseWrite() ==
        Synchronization::LockReleaseResult::Released
    );

    Portable::Synchronization::CountingSemaphoreProvider semaphore;

    assert(
        semaphore.Initialize(
            2U,
            1U
        ) == Synchronization::SemaphoreInitializationResult::Succeeded
    );

    assert(
        semaphore.Acquire(
            Synchronization::WaitTimeout::NoWait()
        ) == Synchronization::SemaphoreAcquireResult::Acquired
    );

    assert(
        semaphore.Acquire(
            Synchronization::WaitTimeout::NoWait()
        ) == Synchronization::SemaphoreAcquireResult::TimedOut
    );

    assert(
        semaphore.Release() ==
        Synchronization::SemaphoreReleaseResult::Released
    );

    assert(
        semaphore.ReleaseFromInterrupt() ==
        Synchronization::SemaphoreReleaseResult::UnsupportedInterruptContext
    );

    Portable::Synchronization::SignalProvider signal;

    assert(
        signal.Notify() ==
        Synchronization::SignalNotifyResult::Signaled
    );

    assert(
        signal.Notify() ==
        Synchronization::SignalNotifyResult::Signaled
    );

    assert(
        signal.Wait(
            Synchronization::WaitTimeout::NoWait()
        ) == Synchronization::SignalWaitResult::Signaled
    );

    assert(
        signal.Wait(
            Synchronization::WaitTimeout::NoWait()
        ) == Synchronization::SignalWaitResult::TimedOut
    );

    Portable::Synchronization::SpinLockProvider spinLock;
    spinLock.Acquire();

    assert(
        spinLock.Release() ==
        Synchronization::SpinLockReleaseResult::Released
    );

    assert(
        spinLock.AcquireFromInterrupt() ==
        Synchronization::SpinLockAcquireResult::UnsupportedInterruptContext
    );

    return 0;
}
