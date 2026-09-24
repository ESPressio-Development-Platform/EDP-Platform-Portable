# src/ESPressio_Platform_Portable_ByteOperations.hpp

**Primary classification:** PUBLIC ENTRY POINT

## Direct includes

- `memory/ByteOperationsProvider.hpp`

## Purpose

This root-level public entry point exports only `ESPressio::Platform::Portable::Memory::ByteOperationsProvider`.

It exists for consumers, including Arduino IDE / Arduino CLI builds, that need the portable ByteOperations concrete without importing unrelated portable atomic or synchronization providers through the complete `ESPressio_Platform_Portable.hpp` umbrella.
