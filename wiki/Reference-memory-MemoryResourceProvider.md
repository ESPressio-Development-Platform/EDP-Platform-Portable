# src/memory/MemoryResourceProvider.hpp

**Primary classification:** PUBLIC PROVIDER / EXTENSION API

**Source baseline:** `ac8b4d22ad8030368db10750f751b2cdf1d58e18`

[Open exact source](https://github.com/ESPressio-Development-Platform/EDP-Platform-Portable/blob/ac8b4d22ad8030368db10750f751b2cdf1d58e18/src/memory/MemoryResourceProvider.hpp)

## Direct includes

- `cstddef`
- `new`
- `ESPressio_Memory.hpp`

## Documented declarations

### `MemoryResourceProvider`

**Classification:** PUBLIC PROVIDER / EXTENSION API

Standard C++17 aligned nothrow raw-memory resource.

```cpp
class MemoryResourceProvider final : public Framework::Provider<
        ESPressio::Memory::Domain,
```

### `IsPowerOfTwo`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Reports whether a non-zero integer is a power of two.

```cpp
static constexpr bool IsPowerOfTwo(
                std::size_t value
            ) noexcept
```

### `NormalizeAlignment`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Normalizes under-aligned requests to the Standard C++ default allocation alignment.

```cpp
static constexpr std::size_t NormalizeAlignment(
                std::size_t alignment
            ) noexcept
```

### `Allocate`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Allocates one aligned raw byte block using C++17 nothrow aligned operator new.

```cpp
ESPressio::Memory::MemoryAllocationResult Allocate(
                std::size_t byteCount,
                std::size_t alignment,
                ESPressio::Memory::MemoryBlock& block
            ) noexcept
```

### `Release`

**Classification:** PUBLIC PROVIDER / EXTENSION API · source access: `public`

Releases one block previously allocated by this provider instance.

```cpp
ESPressio::Memory::MemoryReleaseResult Release(
                const ESPressio::Memory::MemoryBlock& block
            ) noexcept
```

