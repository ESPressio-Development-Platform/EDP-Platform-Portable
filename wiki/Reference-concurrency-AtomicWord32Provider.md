# src/concurrency/AtomicWord32Provider.hpp

**Primary classification:** PUBLIC PROVIDER / EXTENSION API

**Source baseline:** `ac8b4d22ad8030368db10750f751b2cdf1d58e18`

[Open exact source](https://github.com/ESPressio-Development-Platform/EDP-Platform-Portable/blob/ac8b4d22ad8030368db10750f751b2cdf1d58e18/src/concurrency/AtomicWord32Provider.hpp)

## Direct includes

- `atomic`
- `cstdint`
- `ESPressio_Platform.hpp`

## Documented declarations

### `AtomicWord32Provider`

**Classification:** PUBLIC PROVIDER / EXTENSION API

Standard C++ provider for the Platform AtomicWord32 capability.

```cpp
class AtomicWord32Provider final : public Framework::Provider<
        ESPressio::Platform::Domain,
```

### `Word`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Four-byte lock-free atomic word supplied to Platform consumers.

```cpp
class Word final
```

### `_value`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Native 32-bit atomic value owned by this word.

```cpp
std::atomic<std::uint32_t> _value;
```

### `Word`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Creates an atomic word initialized to zero.

```cpp
constexpr Word() noexcept :
                        _value(0U) {}
```

### `Word`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents copying synchronization storage.

```cpp
Word(const Word&) = delete;
```

### `operator`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents copy assignment of synchronization storage.

```cpp
Word& operator =(const Word&) = delete;
```

### `Word`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents relocating synchronization storage.

```cpp
Word(Word&&) = delete;
```

### `operator`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Prevents move assignment of synchronization storage.

```cpp
Word& operator =(Word&&) = delete;
```

### `LoadRelaxed`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Reads the current value without cross-word ordering.

```cpp
std::uint32_t LoadRelaxed() const noexcept
```

### `LoadAcquire`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Reads the current value with acquire ordering.

```cpp
std::uint32_t LoadAcquire() const noexcept
```

### `StoreRelaxed`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Replaces the current value without cross-word ordering.

```cpp
void StoreRelaxed(
                        std::uint32_t value
                    ) noexcept
```

### `StoreRelease`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Replaces the current value with release ordering.

```cpp
void StoreRelease(
                        std::uint32_t value
                    ) noexcept
```

### `CompareExchangeAcqRel`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Replaces the current value when it matches the expected value.

```cpp
bool CompareExchangeAcqRel(
                        std::uint32_t& expected,
                        std::uint32_t desired
                    ) noexcept
```

### `AtomicWord32Contract`

**Classification:** PUBLIC PROVIDER / EXTENSION API

Compile-time validation of the complete AtomicWord32 provider contract.

```cpp
using AtomicWord32Contract = ESPressio::Platform::Concurrency::Detail::AtomicWord32ProviderTraits<AtomicWord32Provider>;
```

