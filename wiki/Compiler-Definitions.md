# Compiler Definitions and Conditional Compilation

No repository-defined compiler definitions were found in the audited PlatformIO/CMake/SDK configuration. Portable provider selection and behaviour are expressed through C++ provider types and contracts rather than repository-specific preprocessor switches.

External standard-library/platform macros are not EDP configuration knobs.

> Audited against `fc533d9e6deaf841f7ebd24f71ef4124e4630436` on `main` across 9 build-configuration file(s).

## Narrow MemoryResource entry point and host CMake closure (9 November 2026)

The new `ESPressio_Platform_Portable_MemoryResource.hpp` is a public **include selector only**; it introduces no repository-owned `#define`, conditional compilation branch, storage knob or override of the existing `AtomicWord32Provider` lock-free `static_assert`. The maintained host `tests/CMakeLists.txt` now requires `EDP_BOUNDED_TOPOLOGY_SOURCE_DIR`, the CMake-only source-root input needed by the transitive `EDP-Memory` header closure. It is **not** a production compiler definition, runtime configuration or newly mandatory package dependency. External ESP-IDF exception and Arduino target selection macros remain owned by their corresponding toolchains, not this portable provider repository.
