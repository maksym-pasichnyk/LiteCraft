#pragma once

#include <compare>
#include <cstdint>
#include <glm/vec3.hpp>

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

    constexpr static auto from(const glm::ivec3& pos) noexcept -> ChunkPos {
        return {pos.x >> 4, pos.z >> 4};
    }

    constexpr static auto from(int32_t x, int32_t z) noexcept -> ChunkPos {
        return {x, z};
    }

    constexpr auto operator<=>(const ChunkPos&) const noexcept = default;

    template<typename T>
    constexpr T cast() const noexcept {
        return T{x, z};
    }

    constexpr static int64_t asLong(int x, int z) noexcept {
        return static_cast<int64_t>(x) & 0xFFFFFFFFLL | (static_cast<int64_t>(z) & 0xFFFFFFFFLL) << 32;
    }

    constexpr int64_t asLong() const noexcept {
        return asLong(x, z);
    }

    constexpr int32_t getStartX() const noexcept {
        return x << 4;
    }

    constexpr int32_t getStartZ() const noexcept {
        return z << 4;
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