# Build, Test and Source Map

C++20 is required. `docs/` describes AtomicWord32, memory providers and synchronization semantics. Host tests are especially important because this repository is the standard host-side provider baseline used by many other EDP libraries.

Arduino-facing consumers that need only ByteOperations should validate through the root-level `ESPressio_Platform_Portable_ByteOperations.hpp` entry point rather than the complete umbrella. This keeps dependency discovery compatible with Arduino while preserving AtomicWord32's lock-free target requirement.
