#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <range/v3/view.hpp>
#include <range/v3/algorithm.hpp>
#include <util/Rotation.hpp>
#include <util/Direction.hpp>

struct BlockPos : glm::ivec3 {
    using glm::ivec3::ivec3;

    constexpr BlockPos(const glm::ivec3& pos) : glm::ivec3(pos) {}

    static constexpr int32_t NUM_X_BITS = 26;
    static constexpr int32_t NUM_Z_BITS = NUM_X_BITS;
    static constexpr int32_t NUM_Y_BITS = 64 - NUM_X_BITS - NUM_Z_BITS;
    static constexpr int64_t X_MASK = (1 << NUM_X_BITS) - 1;
    static constexpr int64_t Y_MASK = (1 << NUM_Y_BITS) - 1;
    static constexpr int64_t Z_MASK = (1 << NUM_Z_BITS) - 1;
    static constexpr int32_t INVERSE_START_BITS_Y = 0;
    static constexpr int32_t INVERSE_START_BITS_Z = NUM_Y_BITS;
    static constexpr int32_t INVERSE_START_BITS_X = NUM_Y_BITS + NUM_Z_BITS;

    static constexpr auto from(int x, int y, int z) -> BlockPos {
        return {x, y, z};
    }

    static constexpr auto pack(int32_t x, int32_t y, int32_t z) -> int64_t {
        return
            ((static_cast<int64_t>(y) & Y_MASK) << INVERSE_START_BITS_Y) |
            ((static_cast<int64_t>(x) & X_MASK) << INVERSE_START_BITS_X) |
            ((static_cast<int64_t>(z) & Z_MASK) << INVERSE_START_BITS_Z);
    }

    static auto getProximitySortedBoxPositions(const BlockPos& pos, int xWidth, int yHeight, int zWidth) {
        const auto i = xWidth + yHeight + zWidth;
        const auto [j, k, l] = pos;
    }

    static auto getAllInBox(int x0, int y0, int z0, int x1, int y1, int z1) {
        const auto dx = x1 - x0 + 1;
        const auto dy = y1 - y0 + 1;
        const auto dz = z1 - z0 + 1;
        return ranges::views::iota(0, dx * dy * dz) | ranges::views::transform([x0, y0, z0, dx, dy](int i) {
            return from(x0 + (i % dx), y0 + ((i / dx) % dy), z0 + (i / dx / dy));
        });
    }

    static auto getAllInBox(const BlockPos& from, const BlockPos& to) {
        return getAllInBox(from.x, from.y, from.z, to.x, to.y, to.z);
    }

    constexpr auto add(const BlockPos& pos) const noexcept -> BlockPos {
        return add(pos.x, pos.y, pos.z);
    }

    constexpr auto add(int dx, int dy, int dz) const noexcept -> BlockPos {
        return from(x + dx, y + dy, z + dz);
    }

    constexpr auto sub(int dx, int dy, int dz) const noexcept -> BlockPos {
        return from(x - dx, y - dy, z - dz);
    }

    constexpr auto up(int n = 1) const noexcept -> BlockPos {
        return from(x, y + n, z);
    }

    constexpr auto down(int n = 1) const noexcept -> BlockPos {
        return from(x, y - n, z);
    }

    constexpr auto south(int n = 1) const noexcept -> BlockPos {
        return from(x, y, z + n);
    }

    constexpr auto north(int n = 1) const noexcept -> BlockPos {
        return from(x, y, z - n);
    }

    constexpr auto east(int n = 1) const noexcept -> BlockPos {
        return from(x + n, y, z);
    }

    constexpr auto west(int n = 1) const noexcept -> BlockPos {
        return from(x - n, y, z);
    }

    auto distanceSq(const BlockPos& to) const -> double {
        return distanceSq(glm::dvec3(to), true);
    }

    auto distanceSq(const glm::dvec3& to, bool useCenter) const -> double {
        const auto delta = glm::dvec3(*this) + glm::dvec3(useCenter ? 0.5 : 0.0) - to;
        return glm::dot(delta, delta);
    }

    constexpr auto offset(Direction direction) const -> BlockPos {
        return *this + DirectionUtil::OFFSET[static_cast<int>(direction)];
    }

    constexpr auto clampAxisCoordinate(DirectionAxis axis, int min, int max) const -> tl::optional<BlockPos> {
        switch (axis) {
            case DirectionAxis::X:
                return from(std::clamp(x, min, max), y, z);
            case DirectionAxis::Y:
                return from(x, std::clamp(y, min, max), z);
            case DirectionAxis::Z:
                return from(x, y, std::clamp(z, min, max));
            default:
                return tl::nullopt;
        }
    }
};