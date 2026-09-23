# Private Implementation

CountingSemaphore uses mutex/condition-variable state because the C++ standard counting-semaphore maximum is a compile-time constant while EDP's capacity is runtime provider state. Signal is a bounded boolean latch. SpinLock uses `atomic_flag` and yields while contended.

Standard-library synchronization may allocate internally; this repository must not mis-advertise deterministic-static behaviour that the standard runtime cannot guarantee.
