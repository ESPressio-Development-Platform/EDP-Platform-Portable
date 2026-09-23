# src/memory/ByteOperationsProvider.hpp

**Primary classification:** PUBLIC PROVIDER / EXTENSION API

**Source baseline:** `ac8b4d22ad8030368db10750f751b2cdf1d58e18`

[Open exact source](https://github.com/ESPressio-Development-Platform/EDP-Platform-Portable/blob/ac8b4d22ad8030368db10750f751b2cdf1d58e18/src/memory/ByteOperationsProvider.hpp)

## Direct includes

- `cstddef`
- `cstdint`
- `cstring`
- `ESPressio_Memory.hpp`

## Documented declarations

### `ByteOperationsProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API

Standard C/C++ implementation of the EDP-Memory ByteOperations capability.

```cpp
class ByteOperationsProvider final : public Framework::Provider<
        ESPressio::Memory::Domain,
```

### `CopyBytes`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Copies one non-overlapping byte range.

```cpp
void CopyBytes(
                void* destination,
                const void* source,
                std::size_t byteCount
            ) const noexcept
```

### `MoveBytes`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Moves one byte range while permitting source/destination overlap.

```cpp
void MoveBytes(
                void* destination,
                const void* source,
                std::size_t byteCount
            ) const noexcept
```

### `FillBytes`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Fills one writable byte range with the requested byte value.

```cpp
void FillBytes(
                void* destination,
                std::uint8_t value,
                std::size_t byteCount
            ) const noexcept
```

### `CompareBytes`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Lexicographically compares two readable ranges as unsigned bytes.

```cpp
ESPressio::Memory::ByteComparison CompareBytes(
                const void* left,
                const void* right,
                std::size_t byteCount
            ) const noexcept
```

