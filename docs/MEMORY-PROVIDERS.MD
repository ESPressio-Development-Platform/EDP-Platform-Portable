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

`Portable::Memory::MemoryResourceProvider` uses the C++20 Standard Library's nothrow aligned `operator new` and matching aligned `operator delete`.

Allocation requires a non-zero byte count and a non-zero power-of-two requested alignment. Requests below `alignof(std::max_align_t)` are normalized upward because the concrete aligned allocation still satisfies the caller's weaker requirement. `MemoryBlock::Alignment` records the actual alignment used for matching release.

Allocation failure is reported as `ResourceExhausted`; no exception escapes the provider.

The provider does not construct objects and does not know Object Pool Types, shared-reserve policy, physical RAM class, or application topology.

## Resource semantics and limitations

This provider represents ordinary Standard C++ dynamic storage. It does not promise static/native deterministic storage, PSRAM placement, DMA accessibility, retention memory, interrupt-context allocation/release, or a bounded heap size.

Applications requiring platform-specific placement select another `MemoryResource` provider through Composition.

## Public import and native ESP32 provider selection

`#include <ESPressio_Platform_Portable_MemoryResource.hpp>` is the single-purpose, Arduino-discoverable root entry point for the existing `Portable::Memory::MemoryResourceProvider`. This is a public include convenience, not another allocation provider, allocation policy, Composition domain or transitive dependency edge. Importing it does not import the full `ESPressio_Platform_Portable.hpp` umbrella, and therefore does not activate the portable `AtomicWord32` requirement or any unrelated Portable synchronization implementation.

On ESP32 Arduino and ESP-IDF, select the actual target's synchronization concrete separately—for example `<ESPressio_Platform_FreeRTOS.hpp>` and its `FreeRTOS::Synchronization::{MutexProvider,SignalProvider}` when an application needs MemoryRuntime locking and wait signaling. The Portable Standard C++ synchronization providers use exception-handling constructs and must not be presumed compatible with an ESP-IDF build that disables exceptions. The full umbrella's lock-free `std::atomic<uint32_t>` requirement remains intentionally enforced; do not suppress it to make an unrelated Memory resource demo compile.

The application declares and owns the providers, and lists concrete application dependencies explicitly. This header does not promise ISR-safe allocation, fixed heap usage, bounded latency, automatic memory-region selection or provider suitability beyond the already documented C++ aligned allocation contract.
