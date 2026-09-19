# EDP-Platform-Portable Dependency Graph

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
