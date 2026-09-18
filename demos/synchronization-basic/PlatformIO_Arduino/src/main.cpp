#include <Arduino.h>

#include <ESPressio_Platform_Portable.hpp>

namespace Demo {

    /// Exercises the portable synchronization providers without requiring another execution context.
    int Run() noexcept {
        using namespace ESPressio::Platform;

        Portable::Synchronization::MutexProvider mutex;

        if (
            mutex.Acquire(
                Synchronization::WaitTimeout::NoWait()
            ) != Synchronization::LockAcquireResult::Acquired
        ) {
            return 1;
        }

        if (
            mutex.Release() !=
            Synchronization::LockReleaseResult::Released
        ) {
            return 2;
        }

        Portable::Synchronization::CountingSemaphoreProvider semaphore;

        if (
            semaphore.Initialize(
                2U,
                1U
            ) != Synchronization::SemaphoreInitializationResult::Succeeded
        ) {
            return 3;
        }

        if (
            semaphore.Acquire(
                Synchronization::WaitTimeout::NoWait()
            ) != Synchronization::SemaphoreAcquireResult::Acquired
        ) {
            return 4;
        }

        if (
            semaphore.Release() !=
            Synchronization::SemaphoreReleaseResult::Released
        ) {
            return 5;
        }

        Portable::Synchronization::SignalProvider signal;

        if (
            signal.Notify() !=
            Synchronization::SignalNotifyResult::Signaled
        ) {
            return 6;
        }

        if (
            signal.Wait(
                Synchronization::WaitTimeout::NoWait()
            ) != Synchronization::SignalWaitResult::Signaled
        ) {
            return 7;
        }

        Portable::Synchronization::SpinLockProvider spinLock;
        spinLock.Acquire();

        return spinLock.Release() ==
            Synchronization::SpinLockReleaseResult::Released
                ? 0
                : 8;
    }

} // Demo


/// Runs the Portable synchronization demonstration once.
void setup() {
    static_cast<void>(
        Demo::Run()
    );
}

/// Leaves the demonstration idle.
void loop() {}
