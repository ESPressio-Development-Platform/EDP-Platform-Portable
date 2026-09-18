# ESPressio Platform Portable

`EDP-Platform-Portable` contains concrete `EDP-Platform` providers implemented entirely with portable Standard C++ facilities.

It contains no Arduino, ESP-IDF or FreeRTOS implementation code.

## Providers

Current providers:

```text
AtomicWord32
Mutex
RecursiveMutex
ReadWriteMutex
CountingSemaphore
Signal
SpinLock
```

`ExecutionContext` is intentionally **not** provided.

The mandated Platform execution contract requires caller-supplied stack and native control storage. `std::thread` does not expose a portable mechanism satisfying that contract, so this repository does not claim the capability.

## Interrupt Context

Standard C++ defines no portable ISR/interrupt execution model.

Therefore:

```text
CountingSemaphore interrupt release    unsupported
Signal interrupt notification          unsupported
SpinLock interrupt operations          unsupported
```

These limitations are advertised through Platform Composition properties.

## Dependencies

```text
EDP-Platform-Portable
└── EDP-Platform [mandatory]
    └── EDP-System [transitive]
```

See [DEPENDENCY_GRAPH.MD](./DEPENDENCY_GRAPH.MD).
