#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>

#include <ESPressio_Memory.hpp>

namespace ESPressio::Platform::Portable::Memory {

    namespace Framework = ESPressio::System::CompositionFramework;

    /// Standard C/C++ implementation of the EDP-Memory ByteOperations capability.
    class ByteOperationsProvider final : public Framework::Provider<
        ESPressio::Memory::Domain,
        Framework::Provides<
            Framework::Offer<ESPressio::Memory::ByteOperations>
        >
    > {

        public:

            // Byte operations.

            /// Copies one non-overlapping byte range.
            void CopyBytes(
                void* destination,
                const void* source,
                std::size_t byteCount
            ) const noexcept {
                if (byteCount == 0U) { return; }

                static_cast<void>(
                    std::memcpy(
                        destination,
                        source,
                        byteCount
                    )
                );
            }

            /// Moves one byte range while permitting source/destination overlap.
            void MoveBytes(
                void* destination,
                const void* source,
                std::size_t byteCount
            ) const noexcept {
                if (byteCount == 0U) { return; }

                static_cast<void>(
                    std::memmove(
                        destination,
                        source,
                        byteCount
                    )
                );
            }

            /// Fills one writable byte range with the requested byte value.
            void FillBytes(
                void* destination,
                std::uint8_t value,
                std::size_t byteCount
            ) const noexcept {
                if (byteCount == 0U) { return; }

                static_cast<void>(
                    std::memset(
                        destination,
                        static_cast<int>(value),
                        byteCount
                    )
                );
            }

            /// Lexicographically compares two readable ranges as unsigned bytes.
            ESPressio::Memory::ByteComparison CompareBytes(
                const void* left,
                const void* right,
                std::size_t byteCount
            ) const noexcept {
                if (byteCount == 0U) { return ESPressio::Memory::ByteComparison::Equal; }

                const auto comparison = std::memcmp(
                    left,
                    right,
                    byteCount
                );

                if (comparison < 0) { return ESPressio::Memory::ByteComparison::Less; }
                if (comparison > 0) { return ESPressio::Memory::ByteComparison::Greater; }

                return ESPressio::Memory::ByteComparison::Equal;
            }

    };


    static_assert(
        sizeof(ESPressio::Memory::Detail::ByteOperationsProviderTraits<ByteOperationsProvider>) > 0U,
        "Portable ByteOperationsProvider must satisfy the EDP-Memory contract"
    );

} // ESPressio::Platform::Portable::Memory
