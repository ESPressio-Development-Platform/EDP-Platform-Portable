# Architecture

The repository provides AtomicWord32 plus standard-library synchronization providers and portable Memory ByteOperations/MemoryResource providers.

It deliberately does not provide ExecutionContext because `std::thread` cannot satisfy the EDP-Platform requirement for caller-supplied native control and stack backing. This is an architectural exclusion, not a missing convenience wrapper.
