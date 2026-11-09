# src/ESPressio_Platform_Portable_MemoryResource.hpp

**Classification:** PUBLIC ENTRY POINT (additive convenience import; no new runtime provider or implementation).

**Source:** [exact public header source](https://github.com/ESPressio-Development-Platform/EDP-Platform-Portable/blob/2bcb9deea411700c32eabf20cbbcb776c96bf6ec/src/ESPressio_Platform_Portable_MemoryResource.hpp).

## Purpose and contract

This root-level public entry point imports **only** `memory/MemoryResourceProvider.hpp`, making the existing `ESPressio::Platform::Portable::Memory::MemoryResourceProvider` directly discoverable by Arduino IDE / Arduino CLI and PlatformIO application sketches. No classes, fields, templates, constants or additional provider interfaces are declared by this wrapper.

The concrete implementation and contract remain in [MemoryResource provider reference](Reference-memory-MemoryResourceProvider) and [Memory Providers](../docs/MEMORY-PROVIDERS.MD): aligned, nothrow Standard C++ dynamic raw storage, with allocation failure reported via the established Memory result type. The caller/application Bootstrap selects the provider through existing Composition. This header does not own Memory pools, allocation quotas, shutdown, thread synchronization or object lifetime.

## Explicit non-contracts

This header does **not** include `ESPressio_Platform_Portable.hpp`; consequently it neither activates the `AtomicWord32Provider` always-lock-free four-byte requirement nor selects the Portable Standard C++ synchronization providers. ESP32 Arduino toolchains that do not satisfy that atomic assertion can use this narrow resource without bypassing it. ESP-IDF builds without exceptions must select suitable independent concrete synchronization providers (for example existing EDP-Platform-FreeRTOS) rather than importing Portable synchronization.

This is a **public import path**, not an additional library dependency: the underlying provider already directly depends on EDP-Memory; EDP-Platform-Portable retains its mandatory EDP-Platform and EDP-Memory dependency graph. It introduces no conditional compiler definition or runtime storage, and no automatic provider selection. Suitable examples are in the consuming EDP-Memory demo families.
