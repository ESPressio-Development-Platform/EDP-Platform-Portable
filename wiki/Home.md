# EDP-Platform-Portable Developer Wiki

EDP-Platform-Portable supplies standard C/C++ implementations of portable EDP-Platform and EDP-Memory capabilities.

This Wiki is maintained beside the code on the same branch as the implementation. The repository-local Wiki remains authoritative, including after any accepted branch promotion to `main`. Source code and repository `docs/` remain normative; the Wiki is the internal developer explanation/navigation layer.

## Public entry points

```cpp
#include <ESPressio_Platform_Portable.hpp> // all concrete providers; enforces AtomicWord32's lock-free contract
#include <ESPressio_Platform_Portable_ByteOperations.hpp> // only ByteOperations
#include <ESPressio_Platform_Portable_MemoryResource.hpp> // only MemoryResource
```

Use the narrow roots for Arduino/library discovery when the broad provider set is not required. An ESP32 application needing a native Mutex/Signal separately selects an appropriate FreeRTOS concrete; no imported root creates a second platform owner.

## Dependencies

Mandatory: EDP-Platform and EDP-Memory.

Use [Architecture](Architecture.md), [Public API](Public-API.md), [Internal API](Internal-API.md), [Implementation](Implementation.md), [Composition](Composition.md), [Resources / Lifecycle / Concurrency](Resources-Lifecycle-Concurrency.md), and [Build / Test / Source](Build-Test-Source.md).
