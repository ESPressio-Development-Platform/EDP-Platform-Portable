#pragma once

#include <atomic>
#include <cstdint>

#include <ESPressio_Platform.hpp>

namespace ESPressio::Platform::Portable::Concurrency {

    namespace Framework = ESPressio::System::CompositionFramework;

    /// Standard C++ provider for the Platform AtomicWord32 capability.
    class AtomicWord32Provider final : public Framework::Provider<
        ESPressio::Platform::Domain,
        Framework::Offers<
            Framework::Offer<
                ESPressio::Platform::Concurrency::AtomicWord32,
                Framework::PropertyValue<ESPressio::Platform::Concurrency::LockFree, true>,
                Framework::PropertyValue<ESPressio::Platform::Concurrency::AtomicWordStorageBytes, 4U>
            >
        >
    > {

        public:

            /// Four-byte lock-free atomic word supplied to Platform consumers.
            class Word final {

                private:

                    // Atomic storage.

                    /// Native 32-bit atomic value owned by this word.
                    std::atomic<std::uint32_t> _value;

                public:

                    // Construction and lifetime.

                    /// Creates an atomic word initialized to zero.
                    constexpr Word() noexcept :
                        _value(0U) {}

                    /// Prevents copying synchronization storage.
                    Word(const Word&) = delete;

                    /// Prevents copy assignment of synchronization storage.
                    Word& operator =(const Word&) = delete;

                    /// Prevents relocating synchronization storage.
                    Word(Word&&) = delete;

                    /// Prevents move assignment of synchronization storage.
                    Word& operator =(Word&&) = delete;


                    // Atomic loads.

                    /// Reads the current value without cross-word ordering.
                    std::uint32_t LoadRelaxed() const noexcept {
                        return _value.load(
                            std::memory_order_relaxed
                        );
                    }

                    /// Reads the current value with acquire ordering.
                    std::uint32_t LoadAcquire() const noexcept {
                        return _value.load(
                            std::memory_order_acquire
                        );
                    }


                    // Atomic stores.

                    /// Replaces the current value without cross-word ordering.
                    void StoreRelaxed(
                        std::uint32_t value
                    ) noexcept {
                        _value.store(
                            value,
                            std::memory_order_relaxed
                        );
                    }

                    /// Replaces the current value with release ordering.
                    void StoreRelease(
                        std::uint32_t value
                    ) noexcept {
                        _value.store(
                            value,
                            std::memory_order_release
                        );
                    }


                    // Atomic compare/exchange.

                    /// Replaces the current value when it matches the expected value.
                    bool CompareExchangeAcqRel(
                        std::uint32_t& expected,
                        std::uint32_t desired
                    ) noexcept {
                        return _value.compare_exchange_strong(
                            expected,
                            desired,
                            std::memory_order_acq_rel,
                            std::memory_order_acquire
                        );
                    }

            };

    };


    static_assert(
        std::atomic<std::uint32_t>::is_always_lock_free,
        "Portable AtomicWord32Provider requires always-lock-free std::atomic<std::uint32_t>"
    );

    static_assert(
        sizeof(std::atomic<std::uint32_t>) == sizeof(std::uint32_t),
        "Portable AtomicWord32Provider requires four-byte std::atomic<std::uint32_t> storage"
    );

    /// Compile-time validation of the complete AtomicWord32 provider contract.
    using AtomicWord32Contract = ESPressio::Platform::Concurrency::Detail::AtomicWord32ProviderTraits<AtomicWord32Provider>;

} // ESPressio::Platform::Portable::Concurrency
