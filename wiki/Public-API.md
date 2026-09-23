# Public API

Platform providers include AtomicWord32, Mutex, RecursiveMutex, ReadWriteMutex, CountingSemaphore, Signal and SpinLock. Memory providers include ByteOperations and a standard dynamic MemoryResource.

AtomicWord32 is only available where `std::atomic<uint32_t>` is always lock-free and exactly four bytes. ByteOperations wraps memcpy/memmove/memset/memcmp semantics with explicit zero-length safety.

Exact declarations remain authoritative in the exported headers.
