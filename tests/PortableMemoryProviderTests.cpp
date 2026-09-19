#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>

#include <ESPressio_Platform_Portable.hpp>

namespace Test {

    namespace Memory = ESPressio::Memory;
    namespace PortableMemory = ESPressio::Platform::Portable::Memory;

    static_assert(
        sizeof(Memory::Detail::ByteOperationsProviderTraits<PortableMemory::ByteOperationsProvider>) > 0U,
        "Portable byte provider must satisfy the Memory contract"
    );

    static_assert(
        sizeof(Memory::Detail::MemoryResourceProviderTraits<PortableMemory::MemoryResourceProvider>) > 0U,
        "Portable resource provider must satisfy the Memory contract"
    );

    /// Exercises the complete Portable EDP-Memory provider surface.
    int Run() noexcept {
        PortableMemory::ByteOperationsProvider bytes;

        std::array<std::uint8_t, 8U> source{
            1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U
        };
        std::array<std::uint8_t, 8U> target{};

        bytes.CopyBytes(
            target.data(),
            source.data(),
            source.size()
        );

        assert(
            bytes.CompareBytes(
                target.data(),
                source.data(),
                source.size()
            ) == Memory::ByteComparison::Equal
        );

        bytes.MoveBytes(
            target.data() + 1U,
            target.data(),
            7U
        );
        assert(target[1U] == 1U);
        assert(target[7U] == 7U);

        bytes.FillBytes(
            target.data(),
            0x5AU,
            target.size()
        );
        for (const auto value : target)
            assert(value == 0x5AU);

        bytes.CopyBytes(nullptr, nullptr, 0U);
        bytes.MoveBytes(nullptr, nullptr, 0U);
        bytes.FillBytes(nullptr, 0U, 0U);
        assert(bytes.CompareBytes(nullptr, nullptr, 0U) == Memory::ByteComparison::Equal);

        PortableMemory::MemoryResourceProvider resource;
        Memory::MemoryBlock unchanged{
            reinterpret_cast<void*>(static_cast<std::uintptr_t>(1U)),
            7U,
            8U
        };

        assert(
            resource.Allocate(
                0U,
                8U,
                unchanged
            ) == Memory::MemoryAllocationResult::InvalidSize
        );
        assert(unchanged.Size == 7U);

        assert(
            resource.Allocate(
                32U,
                3U,
                unchanged
            ) == Memory::MemoryAllocationResult::InvalidAlignment
        );
        assert(unchanged.Size == 7U);

        Memory::MemoryBlock block{};
        assert(
            resource.Allocate(
                128U,
                64U,
                block
            ) == Memory::MemoryAllocationResult::Succeeded
        );
        assert(block.Address != nullptr);
        assert(block.Size == 128U);
        assert(block.Alignment >= 64U);
        assert(
            reinterpret_cast<std::uintptr_t>(block.Address) %
            block.Alignment == 0U
        );

        assert(
            resource.Release(block) ==
            Memory::MemoryReleaseResult::Released
        );

        assert(
            resource.Release(Memory::MemoryBlock{}) ==
            Memory::MemoryReleaseResult::InvalidBlock
        );

        return 0;
    }

} // Test

int main() {
    return Test::Run();
}
