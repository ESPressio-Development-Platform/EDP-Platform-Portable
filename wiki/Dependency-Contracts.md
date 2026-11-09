# Dependency Contracts

EDP-Platform-Portable depends on **EDP-Platform** and **EDP-Memory**.

## EDP-Platform providers

The repository supplies standard-C++ implementations of:

- `AtomicWord32`;
- Mutex;
- RecursiveMutex;
- ReadWriteMutex;
- CountingSemaphore;
- Signal;
- SpinLock.

`AtomicWord32Provider` advertises `LockFree=true` and `AtomicWordStorageBytes=4`; compilation requires `std::atomic<uint32_t>` to satisfy those claims.

Portable synchronization providers advertise their wait-resolution metadata and explicitly advertise **no interrupt-context support** for semaphore release, signal notification and spin-lock operations.

## EDP-Memory providers

`ByteOperationsProvider` offers the Memory `ByteOperations` capability and is the default stateless policy used by EDP-BoundedTypes.

`MemoryResourceProvider` offers `MemoryResource` using C++20 nothrow aligned allocation. This is ordinary dynamic storage and does not claim deterministic-static allocation.

## Explicit non-contract

There is no Portable `ExecutionContext`: `std::thread` cannot satisfy EDP-Platform's caller-supplied native control/stack storage contract.

## Internal provider APIs consumed

The provider implementations compile against EDP-Platform and EDP-Memory provider-trait contracts. Those Detail traits are internal cross-repository APIs even though they are not ordinary application API.

> Dependency contract audit baseline: `0611f72457a3b90281ce5ca2ea1811616ba0d7dd` (`main`).

## Narrow MemoryResource public import (9 November 2026)

The optional public header import `ESPressio_Platform_Portable_MemoryResource.hpp` contains only `memory/MemoryResourceProvider.hpp`. It does not create a third package dependency, another provider, or an automatic Composition selection. Root-level availability supports Arduino IDE/CLI discovery while leaving `AtomicWord32` and Portable synchronization's own (potentially unsupported) compilation constraints unaffected. A consuming application selecting FreeRTOS Mutex/Signal must explicitly name `EDP-Platform-FreeRTOS` as its separate concrete dependency; Portable does not acquire a dependency on FreeRTOS. The complete graph remains acyclic, with mandatory Platform and Memory only.
