#pragma once

#include <compare>
#include <cstdint>
#include <glm/vec3.hpp>

enum class Dimension {
    Overworld = 0,
    Nether = 1,
    End = 2
};

struct ChunkPos {
    int32_t x;
    int32_t z;
//    Dimension dimension;

    constexpr static auto from(const glm::ivec3& pos) noexcept -> ChunkPos {
        return {pos.x >> 4, pos.z >> 4};
    }

    constexpr static auto from(int64_t pack) noexcept -> ChunkPos {
        return {
            static_cast<int32_t>(pack & 0xFFFFFFFFLL),
            static_cast<int32_t>((pack >> 32) & 0xFFFFFFFFLL)
        };
    }

    constexpr static auto from(int32_t x, int32_t z) noexcept -> ChunkPos {
        return {x, z};
    }

    constexpr auto operator<=>(const ChunkPos&) const noexcept = default;

    template<typename T>
    constexpr T cast() const noexcept {
        return T{x, z};
    }

    constexpr static auto asLong(int x, int z) noexcept -> int64_t {
        return static_cast<int64_t>(x) & 0xFFFFFFFFLL | (static_cast<int64_t>(z) & 0xFFFFFFFFLL) << 32;
    }

    constexpr auto asLong() const noexcept -> int64_t {
        return asLong(x, z);
    }

    constexpr auto getStartX() const noexcept -> int32_t {
        return x << 4;
    }

    constexpr auto getStartZ() const noexcept -> int32_t {
        return z << 4;
    }

    constexpr auto getEndX() const noexcept -> int32_t {
        return getStartX() + 15;
    }

    constexpr auto getEndZ() const noexcept -> int32_t {
        return getStartZ() + 15;
    }

    constexpr auto getBlockX(int offset) const noexcept -> int32_t {
        return getStartX() + offset;
    }

    constexpr auto getBlockZ(int offset) const noexcept -> int32_t {
        return getStartZ() + offset;
    }

    constexpr auto getBlockPos(int _x, int _y, int _z) const noexcept -> BlockPos {
        return BlockPos::from(getBlockX(_x), _y, getBlockZ(_z));
    }

    constexpr auto getStartBlock() const noexcept -> BlockPos {
        return BlockPos::from(getStartX(), 0, getStartZ());
    }
};