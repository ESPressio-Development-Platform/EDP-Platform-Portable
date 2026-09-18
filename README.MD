# ESPressio Platform Portable

`EDP-Platform-Portable` contains concrete `EDP-Platform` providers implemented entirely with portable Standard C++ facilities.

It contains no Arduino, ESP-IDF, or FreeRTOS implementation code.

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

`ExecutionContext` is intentionally not provided because portable `std::thread` cannot satisfy the Platform requirement for caller-supplied native control and stack storage.

## Documentation

- [AtomicWord32 Provider](./docs/ATOMIC-WORD-32.MD)  
  Defines the lock-free four-byte Standard C++ atomic provider and its exact memory-order surface.

- [Synchronization Providers](./docs/SYNCHRONIZATION.MD)  
  Defines the Standard C++ mutex, reader/writer lock, counting semaphore, signal, and spin-lock providers, including timeout, failure, interrupt, and resource semantics.

## Dependencies

```text
EDP-Platform-Portable
└── EDP-Platform [mandatory]
    └── EDP-System [transitive]
```

There are no optional ESPressio library dependencies.

See [DEPENDENCY_GRAPH.MD](./DEPENDENCY_GRAPH.MD).

## Demos

Buildable demonstrations are provided under [`./demos`](./demos) for the Portable atomic and synchronization providers.
