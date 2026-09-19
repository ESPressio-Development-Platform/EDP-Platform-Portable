#include <Arduino.h>

#include <array>
#include <cstdint>

#include <ESPressio_Platform_Portable.hpp>

namespace Demo {

    /// Demonstrates the Portable Standard C/C++ ByteOperations provider.
    int Run() noexcept {
        ESPressio::Platform::Portable::Memory::ByteOperationsProvider provider;

        std::array<std::uint8_t, 4U> source{1U, 2U, 3U, 4U};
        std::array<std::uint8_t, 4U> target{};

        provider.CopyBytes(target.data(), source.data(), source.size());

        return provider.CompareBytes(
            target.data(),
            source.data(),
            source.size()
        ) == ESPressio::Memory::ByteComparison::Equal ? 0 : 1;
    }

} // Demo

void setup() {
    static_cast<void>(Demo::Run());
}

void loop() {}
