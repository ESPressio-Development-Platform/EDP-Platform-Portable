# AtomicWord8 Provider

## Purpose

`AtomicWord8Provider` supplies the Platform `AtomicWord8` capability using Standard C++ `std::atomic<std::uint8_t>`.

It exists for compact cross-context control words whose complete state can be represented in one byte. Higher domains such as EDP-Threading can therefore preserve one-byte packed lifecycle/control representations without embedding Standard C++ atomic implementation choices directly.

## Contract

The provider guarantees:

```text
AtomicWord8LockFree       = true
AtomicWord8StorageBytes   = 1
```

The build is rejected if `std::atomic<std::uint8_t>` is not always lock-free or does not occupy exactly one byte.

The nested `Word` supports relaxed/acquire loads, relaxed/release stores and acquire-release compare/exchange. It is default-constructible, non-copyable and non-movable.

## Ownership

Each `Word` owns exactly one byte of atomic state and performs no dynamic allocation.
