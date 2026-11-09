# Demos

The Portable provider repository includes:

- `atomic-word-basic` — Standard C++ `AtomicWord32` provider;
- `synchronization-basic` — Standard C++ mutex, counting semaphore, signal and spin-lock providers;
- `byte-operations-basic` — Standard C/C++ raw byte operations satisfying EDP-Memory;
- `memory-resource-basic` — C++20-aligned nothrow raw allocation satisfying EDP-Memory, now demonstrated via `<ESPressio_Platform_Portable_MemoryResource.hpp>`, without importing unrelated atomic/synchronization constraints.

Each demo provides Arduino IDE, PlatformIO Arduino and PlatformIO ESP-IDF sources. This source availability does **not** automatically mean that every provider is supported by every toolchain: the broad Portable AtomicWord32 implementation requires always-lock-free four-byte `std::atomic<uint32_t>`, and Standard C++ synchronization includes exception handling that an ESP-IDF configuration may disable. Do not weaken these contracts or report the corresponding unsupported concrete as a passing ESP32 demo. The narrow MemoryResource example is separately qualified on both PlatformIO ESP32 targets.

`ExecutionContext` remains intentionally absent because Standard C++ does not expose the caller-supplied stack/control-storage contract required by `EDP-Platform`.

## C++ Language Baseline

All PlatformIO-compatible demos require C++20 and explicitly select the maintained PIOArduino ESP32 platform package.
