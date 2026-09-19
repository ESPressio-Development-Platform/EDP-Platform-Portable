#include <cstdint>

#include <ESPressio_Platform_Portable.hpp>

namespace Demo {

    /// Demonstrates one explicit aligned allocation and release through EDP-Memory contracts.
    int Run() noexcept {
        ESPressio::Platform::Portable::Memory::MemoryResourceProvider provider;
        ESPressio::Memory::MemoryBlock block{};

        if (
            provider.Allocate(
                128U,
                32U,
                block
            ) != ESPressio::Memory::MemoryAllocationResult::Succeeded
        ) {
            return 1;
        }

        if (
            reinterpret_cast<std::uintptr_t>(block.Address) %
            block.Alignment != 0U
        ) {
            return 2;
        }

        return provider.Release(block) ==
            ESPressio::Memory::MemoryReleaseResult::Released ? 0 : 3;
    }

} // Demo

extern "C" void app_main() {
    static_cast<void>(Demo::Run());
}
