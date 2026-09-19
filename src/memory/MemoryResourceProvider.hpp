#pragma once

#include <cstddef>
#include <new>

#include <ESPressio_Memory.hpp>

namespace ESPressio::Platform::Portable::Memory {

    namespace Framework = ESPressio::System::CompositionFramework;

    /// Standard C++17 aligned nothrow raw-memory resource.
    class MemoryResourceProvider final : public Framework::Provider<
        ESPressio::Memory::Domain,
        Framework::Provides<
            Framework::Offer<ESPressio::Memory::MemoryResource>
        >
    > {

        private:

            /// Reports whether a non-zero integer is a power of two.
            static constexpr bool IsPowerOfTwo(
                std::size_t value
            ) noexcept {
                return value != 0U && (value & (value - 1U)) == 0U;
            }

            /// Normalizes under-aligned requests to the Standard C++ default allocation alignment.
            static constexpr std::size_t NormalizeAlignment(
                std::size_t alignment
            ) noexcept {
                return alignment < alignof(std::max_align_t)
                    ? alignof(std::max_align_t)
                    : alignment;
            }

        public:

            /// Allocates one aligned raw byte block using C++17 nothrow aligned operator new.
            ESPressio::Memory::MemoryAllocationResult Allocate(
                std::size_t byteCount,
                std::size_t alignment,
                ESPressio::Memory::MemoryBlock& block
            ) noexcept {
                if (byteCount == 0U) {
                    return ESPressio::Memory::MemoryAllocationResult::InvalidSize;
                }

                if (!IsPowerOfTwo(alignment)) {
                    return ESPressio::Memory::MemoryAllocationResult::InvalidAlignment;
                }

                const auto actualAlignment = NormalizeAlignment(alignment);
                void* allocation = ::operator new(
                    byteCount,
                    std::align_val_t(actualAlignment),
                    std::nothrow
                );

                if (allocation == nullptr) {
                    return ESPressio::Memory::MemoryAllocationResult::ResourceExhausted;
                }

                ESPressio::Memory::MemoryBlock candidate;
                candidate.Address = allocation;
                candidate.Size = byteCount;
                candidate.Alignment = actualAlignment;
                block = candidate;

                return ESPressio::Memory::MemoryAllocationResult::Succeeded;
            }

            /// Releases one block previously allocated by this provider instance.
            ESPressio::Memory::MemoryReleaseResult Release(
                const ESPressio::Memory::MemoryBlock& block
            ) noexcept {
                if (
                    block.Address == nullptr ||
                    block.Size == 0U ||
                    !IsPowerOfTwo(block.Alignment)
                ) {
                    return ESPressio::Memory::MemoryReleaseResult::InvalidBlock;
                }

                ::operator delete(
                    block.Address,
                    std::align_val_t(block.Alignment)
                );

                return ESPressio::Memory::MemoryReleaseResult::Released;
            }

    };


    static_assert(
        sizeof(ESPressio::Memory::Detail::MemoryResourceProviderTraits<MemoryResourceProvider>) > 0U,
        "Portable MemoryResourceProvider must satisfy the EDP-Memory contract"
    );

} // ESPressio::Platform::Portable::Memory
