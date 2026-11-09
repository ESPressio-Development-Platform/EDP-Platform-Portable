# Public API

Platform providers include AtomicWord32, Mutex, RecursiveMutex, ReadWriteMutex, CountingSemaphore, Signal and SpinLock. Memory providers include ByteOperations and a standard dynamic MemoryResource.

AtomicWord32 is only available where `std::atomic<uint32_t>` is always lock-free and exactly four bytes. ByteOperations wraps memcpy/memmove/memset/memcmp semantics with explicit zero-length safety.

Exact declarations remain authoritative in the exported headers.

## Root-level public entry points

`ESPressio_Platform_Portable.hpp` is the complete portable-provider umbrella.

`ESPressio_Platform_Portable_ByteOperations.hpp` is the narrow public entry point for only `Platform::Portable::Memory::ByteOperationsProvider`. It allows Arduino dependency discovery without importing unrelated atomic/synchronization providers and without weakening their target contracts.

`ESPressio_Platform_Portable_MemoryResource.hpp` is the distinct narrow public import for the already existing `Portable::Memory::MemoryResourceProvider`. It includes only `memory/MemoryResourceProvider.hpp`, introduces no new declarations, and supports Arduino library discovery without activating unrelated atomics or exception-using synchronization. The user selects concrete synchronization independently; ESP32 demos should use FreeRTOS where appropriate. See [MemoryResource entry point](Reference-ESPressio-Platform-Portable-MemoryResource).
