#pragma once

#include <stdint.hpp>

struct ChunkPos {
    int32 x;
    int32 z;

    constexpr auto operator<=>(const ChunkPos&) const noexcept = default;

    template<typename T>
    constexpr auto cast() -> T {
        return T{x, z};
    }

    constexpr static auto asLong(int x, int z) -> int64 {
        return (int64) x & 0xFFFFFFFFLL | ((int64) z & 0xFFFFFFFFLL) << 32;
    }

    constexpr auto asLong() -> int64 {
        return asLong(x, z);
    }
};
