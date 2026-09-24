# Public API

Platform providers include AtomicWord32, Mutex, RecursiveMutex, ReadWriteMutex, CountingSemaphore, Signal and SpinLock. Memory providers include ByteOperations and a standard dynamic MemoryResource.

AtomicWord32 is only available where `std::atomic<uint32_t>` is always lock-free and exactly four bytes. ByteOperations wraps memcpy/memmove/memset/memcmp semantics with explicit zero-length safety.

Exact declarations remain authoritative in the exported headers.

## Root-level public entry points

`ESPressio_Platform_Portable.hpp` is the complete portable-provider umbrella.

`ESPressio_Platform_Portable_ByteOperations.hpp` is the narrow public entry point for only `Platform::Portable::Memory::ByteOperationsProvider`. It allows Arduino dependency discovery without importing unrelated atomic/synchronization providers and without weakening their target contracts.
