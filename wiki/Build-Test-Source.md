# Build, Test and Source Map

C++20 is required. `docs/` describes AtomicWord32, memory providers and synchronization semantics. Host tests are especially important because this repository is the standard host-side provider baseline used by many other EDP libraries.

Arduino-facing consumers that need only ByteOperations should validate through the root-level `ESPressio_Platform_Portable_ByteOperations.hpp` entry point rather than the complete umbrella. This keeps dependency discovery compatible with Arduino while preserving AtomicWord32's lock-free target requirement.

The single-purpose `ESPressio_Platform_Portable_MemoryResource.hpp` similarly exposes the existing MemoryResource concrete without selecting AtomicWord32, Portable mutexes or exception-using Standard C++ synchronization. ESP32 Arduino/ESP-IDF Memory demos should select FreeRTOS synchronization separately and explicitly declare the concrete library. A root include is required for Arduino IDE/CLI library discovery. This provider-level addition is validated on both Arduino-ESP32 and ESP-IDF in the Memory `topology-teardown-basic` demo; verify that applications use exact selected source branches and not an accidentally transitive `Memory/main` checkout.

## Reproducible validation definitions

The checked-in [`.github/workflows/validation.yml`](../.github/workflows/validation.yml) maintains dual GCC/Clang C++20 provider contracts plus PlatformIO Arduino/ESP-IDF narrow-resource demo builds. The workflow requires actual System, Platform, Memory and BoundedTopology source roots; `EDP_BOUNDED_TOPOLOGY_SOURCE_DIR` closes the transitive current Memory include path. Authoritative execution evidence remains the deliberately detached RPI400 runs and associated Policy/main handoffs, not an assumed GitHub Actions run. No new Portable production source definition or concrete Mutex/Signal implementation was introduced.
