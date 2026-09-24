# EDP-Platform-Portable Dependency Graph

> Revalidated: 2026-09-24 — adding a narrow Arduino-discoverable ByteOperations public entry point changes no dependency edge. During the Primitive-introduction workstream, this feature branch pins the already-modified EDP-Memory dependency to its matching `feature/primitives_introduction` branch for coherent validation.


> Revalidated: 2026-09-23 — Composition Framework enhancement migration changes compile-time provider/requirement metadata and validation only; no ESPressio-library dependency edge changed.

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
