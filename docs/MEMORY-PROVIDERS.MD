# Portable Memory Providers

## Ownership boundary

`EDP-Platform-Portable` owns concrete EDP-Memory providers whose implementations use only Standard C/C++ APIs.

The abstractions remain in `EDP-Memory`; this repository supplies no topology, Object Pool, quota, fallback, or shared-reserve policy.

## ByteOperationsProvider

`Portable::Memory::ByteOperationsProvider` is stateless and uses:

- `std::memcpy` for non-overlapping `CopyBytes`;
- `std::memmove` for overlap-safe `MoveBytes`;
- `std::memset` for `FillBytes`;
- `std::memcmp` for unsigned-byte lexicographical `CompareBytes`.

A zero byte count returns without invoking the library operation, so no memory range is accessed.

The provider performs no allocation, synchronization, object construction, object destruction, or secure-erasure guarantee.

## MemoryResourceProvider

`Portable::Memory::MemoryResourceProvider` uses C++17 nothrow aligned `operator new` and matching aligned `operator delete`.

Allocation requires a non-zero byte count and a non-zero power-of-two requested alignment. Requests below `alignof(std::max_align_t)` are normalized upward because the concrete aligned allocation still satisfies the caller's weaker requirement. `MemoryBlock::Alignment` records the actual alignment used for matching release.

Allocation failure is reported as `ResourceExhausted`; no exception escapes the provider.

The provider does not construct objects and does not know Object Pool Types, shared-reserve policy, physical RAM class, or application topology.

## Resource semantics and limitations

This provider represents ordinary Standard C++ dynamic storage. It does not promise static/native deterministic storage, PSRAM placement, DMA accessibility, retention memory, interrupt-context allocation/release, or a bounded heap size.

Applications requiring platform-specific placement select another `MemoryResource` provider through Composition.
