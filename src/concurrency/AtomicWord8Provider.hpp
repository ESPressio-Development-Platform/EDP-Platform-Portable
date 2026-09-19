#pragma once

#include <atomic>
#include <cstdint>

#include <ESPressio_Platform.hpp>

namespace ESPressio::Platform::Portable::Concurrency {

    namespace Framework = ESPressio::System::CompositionFramework;

    /// Standard C++ provider for the compact Platform AtomicWord8 capability.
    class AtomicWord8Provider final : public Framework::Provider<
        ESPressio::Platform::Domain,
        Framework::Provides<
            Framework::Offer<
                ESPressio::Platform::Concurrency::AtomicWord8,
                Framework::PropertyValue<ESPressio::Platform::Concurrency::AtomicWord8LockFree, true>,
                Framework::PropertyValue<ESPressio::Platform::Concurrency::AtomicWord8StorageBytes, 1U>
            >
        >
    > {

        public:

            /// One-byte lock-free atomic word supplied to Platform consumers.
            class Word final {

                private:

                    // Atomic storage.

                    /// Native one-byte atomic value owned by this word.
                    std::atomic<std::uint8_t> _value;

                public:

                    // Construction and lifetime.

                    /// Creates an atomic byte initialized to zero.
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
                    std::uint8_t LoadRelaxed() const noexcept {
                        return _value.load(
                            std::memory_order_relaxed
                        );
                    }

                    /// Reads the current value with acquire ordering.
                    std::uint8_t LoadAcquire() const noexcept {
                        return _value.load(
                            std::memory_order_acquire
                        );
                    }


                    // Atomic stores.

                    /// Replaces the current value without cross-word ordering.
                    void StoreRelaxed(
                        std::uint8_t value
                    ) noexcept {
                        _value.store(
                            value,
                            std::memory_order_relaxed
                        );
                    }

                    /// Replaces the current value with release ordering.
                    void StoreRelease(
                        std::uint8_t value
                    ) noexcept {
                        _value.store(
                            value,
                            std::memory_order_release
                        );
                    }


                    // Atomic compare/exchange.

                    /// Replaces the current value when it matches the expected value.
                    bool CompareExchangeAcqRel(
                        std::uint8_t& expected,
                        std::uint8_t desired
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
        std::atomic<std::uint8_t>::is_always_lock_free,
        "Portable AtomicWord8Provider requires always-lock-free std::atomic<std::uint8_t>"
    );

    static_assert(
        sizeof(std::atomic<std::uint8_t>) == sizeof(std::uint8_t),
        "Portable AtomicWord8Provider requires one-byte std::atomic<std::uint8_t> storage"
    );

    using AtomicWord8Contract = ESPressio::Platform::Concurrency::Detail::AtomicWord8ProviderTraits<AtomicWord8Provider>;

} // ESPressio::Platform::Portable::Concurrency
