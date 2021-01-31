#pragma once

#include <compare>
#include <cstdint>

enum class Dimension {
    Overworld = 0,
    Nether = 1,
    End = 2
};

//struct SubchunkPos {
//    int32_t x;
//    int32_t z;
//    uint8_t subchunk;
//    Dimension dimension;
//
//    constexpr auto operator<=>(const ChunkPos&) const noexcept = default;
//};

struct ChunkPos {
    int32_t x;
    int32_t z;
//    Dimension dimension;

    constexpr auto operator<=>(const ChunkPos&) const noexcept = default;

    template<typename T>
    constexpr auto cast() -> T {
        return T{x, z};
    }

    constexpr static auto asLong(int x, int z) -> int64_t {
        return static_cast<int64_t>(x) & 0xFFFFFFFFLL | (static_cast<int64_t>(z) & 0xFFFFFFFFLL) << 32;
    }

    constexpr auto asLong() const -> int64_t {
        return asLong(x, z);
    }

//    constexpr SubchunkPos subchunkPos(uint8_t subchunk) const {
//        return { x, z, subchunk, dimension };
//    }
};

//struct WorldPos {
//    int32_t x;
//    uint8_t y;
//    int32_t z;
//    Dimension dimension;
//
//    constexpr ChunkPos chunkPos() const {
//        return { x >> 4, z >> 4, dimension };
//    }
//
//    constexpr int32 subchunkIndex() const {
//        return y >> 4;
//    }
//
//    constexpr int32_t blockIndex() const {
//        const auto inner_x = x & 15;
//        const auto inner_y = y & 15;
//        const auto inner_z = z & 15;
//
//        return (inner_x << 8) | (inner_z << 4) | inner_y;
//    }
//};