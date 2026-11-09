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
- `<ESPressio_Platform_Portable_ByteOperations.hpp>` imports only the portable `EDP-Memory::ByteOperations` concrete, without activating unrelated atomic or synchronization provider constraints.
- `<ESPressio_Platform_Portable_MemoryResource.hpp>` imports **only** the existing portable `EDP-Memory::MemoryResource` concrete. Arduino IDE/CLI and PlatformIO application code can discover the library through this public root header without importing `AtomicWord32` or Portable Synchronization. On ESP32, select separately supported FreeRTOS Mutex/Signal providers when needed; portable synchronization uses Standard C++ exceptions that ESP-IDF builds may disable.

The narrow entry points exist so Arduino IDE / Arduino CLI can discover this library from a root-level public header without requiring a consumer to include an internal `src/memory/...` path.


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

Demonstration projects are provided under [the demo index](./demos/README.MD) for Portable atomic, synchronization, byte-operation and raw-memory-resource providers. Every family supplies Arduino IDE, PlatformIO Arduino and PlatformIO ESP-IDF source variants. Provider target constraints must be enforced: an unsupported lock-free atomic or exception-enabled synchronization composition must fail rather than be silently treated as qualified.

## Testing

Host tests cover the Platform providers plus the Memory byte/resource provider contracts and behaviour. The narrow root imports are independently exercised in the Memory host test; the `memory-resource-basic` PlatformIO Arduino and ESP-IDF examples compile on the authorised RPI400 execution appliance. The [maintained host and target validation workflow](./.github/workflows/validation.yml) is included for reproducibility, but an Actions workflow's existence is not evidence of execution. Portable Memory providers are suitable for host sanitizer validation because they use Standard C/C++ facilities.

## C++ Language Baseline

ESPressio requires C++20. PlatformIO-compatible ESP32 demos use the maintained PIOArduino platform package so Arduino-ESP32 and ESP-IDF builds share a current C++20-capable baseline.
