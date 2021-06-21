#pragma once

#include "../Direction.hpp"

#include <ranges>
#include <cstdint>
#include <glm/glm.hpp>

struct BlockPos : glm::ivec3 {
    using glm::ivec3::ivec3;
    constexpr BlockPos(const glm::ivec3& pos) : glm::ivec3(pos) {}

    static constexpr int NUM_X_BITS = 26;
    static constexpr int NUM_Z_BITS = NUM_X_BITS;
    static constexpr int NUM_Y_BITS = 64 - NUM_X_BITS - NUM_Z_BITS;
    static constexpr long X_MASK = (1L << NUM_X_BITS) - 1L;
    static constexpr long Y_MASK = (1L << NUM_Y_BITS) - 1L;
    static constexpr long Z_MASK = (1L << NUM_Z_BITS) - 1L;
    static constexpr int INVERSE_START_BITS_Z = NUM_Y_BITS;
    static constexpr int INVERSE_START_BITS_X = NUM_Y_BITS + NUM_Z_BITS;

    static constexpr BlockPos from(int x, int y, int z) {
        return {x, y, z};
    }

    static constexpr int64_t pack(int32_t x, int32_t y, int32_t z) {
        return
            ((static_cast<int64_t>(y) & Y_MASK) << 0) |
            ((static_cast<int64_t>(x) & X_MASK) << INVERSE_START_BITS_X) |
            (static_cast<int64_t>(z) & Z_MASK) << INVERSE_START_BITS_Z;
    }

    static auto getAllInBox(int x0, int y0, int z0, int x1, int y1, int z1) {
        const int dx = x1 - x0 + 1;
        const int dy = y1 - y0 + 1;
        const int dz = z1 - z0 + 1;
        return std::views::iota(0, dx * dy * dz) | std::views::transform([x0, y0, z0, dx, dy](int current) {
            return glm::ivec3{x0 + (current % dx), y0 + ((current / dx) % dy), z0 + (current / dx / dy)};
        });
    }

    static auto getAllInBox(const glm::ivec3& from, const glm::ivec3& to) {
        return getAllInBox(from.x, from.y, from.z, to.x, to.y, to.z);
    }

    constexpr auto add(int dx, int dy, int dz) const noexcept {
        return BlockPos{x + dx, y + dy, z + dz};
    }

    constexpr auto sub(int dx, int dy, int dz) const noexcept {
        return BlockPos{x - dx, y - dy, z - dz};
    }

    constexpr auto up(int n = 1) const noexcept {
        return BlockPos{x, y + n, z};
    }

    constexpr auto down(int n = 1) const noexcept {
        return BlockPos{x, y - n, z};
    }

    constexpr auto south(int n = 1) const noexcept {
        return BlockPos{x, y, z + n};
    }

    constexpr auto north(int n = 1) const noexcept {
        return BlockPos{x, y, z - n};
    }

    constexpr auto east(int n = 1) const noexcept {
        return BlockPos{x + n, y, z};
    }

    constexpr auto west(int n = 1) const noexcept {
        return BlockPos{x - n, y, z};
    }

    double distanceSq(const glm::ivec3& to) {
        return distanceSq(glm::dvec3(to), true);
    }

//    double distanceSq(IPosition position, bool useCenter) {
//        return distanceSq(position.x, position.y, position.z, useCenter);
//    }

    double distanceSq(const glm::dvec3& to, bool useCenter) {
        const auto delta = glm::dvec3(*this) + glm::dvec3(useCenter ? 0.5 : 0.0) - to;
        return glm::dot(delta, delta);
    }

    constexpr BlockPos offset(Direction direction) const {
        return BlockPos(*this + DirectionUtil::OFFSET[static_cast<int>(direction)]);
    }
};