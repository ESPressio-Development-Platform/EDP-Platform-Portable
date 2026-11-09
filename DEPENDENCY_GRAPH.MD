# EDP-Platform-Portable Dependency Graph

> Revalidated: 2026-09-24 — adding a narrow Arduino-discoverable ByteOperations public entry point changes no dependency edge. Following reintegration, the existing EDP-Memory dependency resolves from permanent `main`.


> Revalidated: 2026-09-23 — Composition Framework enhancement migration changes compile-time provider/requirement metadata and validation only; no ESPressio-library dependency edge changed.

 > Revalidated: 2026-11-09 — adding the narrow root `ESPressio_Platform_Portable_MemoryResource.hpp` changes no package or Composition dependency. The entry point merely exposes the existing concrete MemoryResource provider without importing the portable atomics/synchronization bundle. Native ESP32 applications may separately choose `EDP-Platform-FreeRTOS` when requiring Mutex/Signal, an **application-owned conditional concrete** rather than an EDP-Platform-Portable dependency.

## Library Dependency Tree

```text
EDP-Platform-Portable
├── EDP-Platform [mandatory]
│   └── EDP-System [mandatory]
└── EDP-Memory [mandatory]
    ├── EDP-System [mandatory]
    └── EDP-Platform [mandatory]
        └── EDP-System [mandatory, transitive]
```

## Mandatory Dependencies

- `EDP-Platform` — defines Platform capabilities implemented by the Portable synchronization/concurrency providers.
- `EDP-Memory` — defines the ByteOperations and MemoryResource contracts implemented by the Portable Memory providers.

`EDP-System` is reached transitively and supplies the Composition Framework.

## Optional Dependencies

`EDP-Platform-Portable` has no optional ESPressio-library dependencies.

## Dependency direction

The dependency remains acyclic because `EDP-Memory` never depends on this concrete provider repository. Application Bootstrap selects these providers through Composition.

> Revalidated 2026-09-20: removal of the rejected AtomicWord8 experiment introduces no dependency change.
