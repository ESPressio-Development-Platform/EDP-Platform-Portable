# Demos

The Portable provider repository includes:

- `atomic-word-basic` — Standard C++ `AtomicWord32` provider;
- `synchronization-basic` — Standard C++ mutex, counting semaphore, signal and spin-lock providers.

Each demo provides the policy-required Arduino IDE, PlatformIO Arduino and PlatformIO ESP-IDF surfaces.

`ExecutionContext` is intentionally absent because Standard C++ does not expose the caller-supplied stack/control-storage contract required by `EDP-Platform`.
