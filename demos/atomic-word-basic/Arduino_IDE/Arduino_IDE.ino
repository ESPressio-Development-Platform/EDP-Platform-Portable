#include <Arduino.h>

#include <ESPressio_Platform_Portable.hpp>

namespace Demo {

    /// Verifies the portable AtomicWord32 provider with one release/acquire round trip.
    int Run() noexcept {
        ESPressio::Platform::Portable::Concurrency::AtomicWord32Provider::Word word;

        word.StoreRelease(
            42U
        );

        return word.LoadAcquire() == 42U ? 0 : 1;
    }

} // Demo

/// Runs the Portable AtomicWord32 demonstration once.
void setup() {
    static_cast<void>(
        Demo::Run()
    );
}

/// Leaves the demonstration idle.
void loop() {}
