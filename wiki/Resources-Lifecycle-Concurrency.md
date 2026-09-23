# Resources, Lifecycle and Concurrency

AtomicWord32 has exact four-byte lock-free storage. ByteOperations owns no state. Portable MemoryResource uses nothrow aligned `new/delete` and is ordinary dynamic storage. Synchronization objects may inherit implementation-specific runtime allocation from the C++ standard library. No ISR capability is advertised.
