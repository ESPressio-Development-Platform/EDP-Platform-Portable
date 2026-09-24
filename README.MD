# ESPressio Platform Portable

`EDP-Platform-Portable` contains concrete providers implemented entirely with portable Standard C/C++ facilities.

It contains no Arduino-, ESP-IDF-, or FreeRTOS-specific implementation code.

## Providers

```text
EDP-Platform
    AtomicWord32
    Mutex
    RecursiveMutex
    ReadWriteMutex
    CountingSemaphore
    Signal
    SpinLock

EDP-Memory
    ByteOperations
    MemoryResource
```

`ExecutionContext` is intentionally not provided because portable `std::thread` cannot satisfy the Platform requirement for caller-supplied native control and stack storage.

## Public entry points

- `<ESPressio_Platform_Portable.hpp>` imports the complete portable provider set and therefore enforces every provider's target contract, including the always-lock-free requirement of `AtomicWord32Provider`.
- `<ESPressio_Platform_Portable_ByteOperations.hpp>` imports only the portable `EDP-Memory::ByteOperations` concrete. Use this narrower public entry point when an application needs byte operations without also selecting unrelated portable atomic/synchronization providers.

The narrow entry point exists specifically so Arduino IDE / Arduino CLI can discover this library from a root-level public header without requiring a consumer to include an internal `src/memory/...` path.


## Documentation

- [AtomicWord32 Provider](./docs/ATOMIC-WORD-32.MD) — lock-free four-byte Standard C++ atomic provider.
- [Synchronization Providers](./docs/SYNCHRONIZATION.MD) — Standard C++ synchronization providers and their timeout/failure/interrupt semantics.
- [Memory Providers](./docs/MEMORY-PROVIDERS.MD) — Standard C/C++ ByteOperations and C++20-aligned nothrow MemoryResource providers.

## Dependencies

```text
EDP-Platform-Portable
├── EDP-Platform [mandatory]
│   └── EDP-System [mandatory]
└── EDP-Memory [mandatory]
    ├── EDP-System [mandatory]
    └── EDP-Platform [mandatory]
```

There are no optional ESPressio-library dependencies.

See [DEPENDENCY_GRAPH.MD](./DEPENDENCY_GRAPH.MD).

## Demos

Buildable demonstrations are provided under [`./demos`](./demos) for Portable atomic, synchronization, byte-operation, and raw-memory-resource providers. Each logical demo provides Arduino IDE, PlatformIO Arduino, and PlatformIO ESP-IDF surfaces.

## Testing

Host tests cover the Platform providers plus the Memory byte/resource provider contracts and behavior. Portable Memory providers are suitable for host sanitizer validation because they use only Standard C/C++ facilities.

## C++ Language Baseline

ESPressio requires C++20. PlatformIO-compatible ESP32 demos use the maintained PIOArduino platform package so Arduino-ESP32 and ESP-IDF builds share a current C++20-capable baseline.
