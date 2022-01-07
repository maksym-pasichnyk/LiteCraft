#pragma once

#include <tuple>
#include <utility>
#include <glm/glm.hpp>

template<>
struct std::less<glm::ivec3> {
    inline constexpr bool operator()(const glm::ivec3& a, const glm::ivec3& b) const noexcept {
        return std::tie(a.x, a.y, a.z) < std::tie(b.x, b.y, b.z);
    }
};
template<>
struct std::less<BlockPos> {
    inline constexpr bool operator()(const BlockPos& a, const BlockPos& b) const noexcept {
        return std::tie(a.x, a.y, a.z) < std::tie(b.x, b.y, b.z);
    }
};