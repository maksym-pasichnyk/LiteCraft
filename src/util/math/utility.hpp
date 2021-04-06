#pragma once

#include <tuple>
#include <utility>
#include <glm/glm.hpp>

namespace std {
    template<>
    struct less<glm::ivec3> {
        inline constexpr bool operator()(const glm::ivec3& a, const glm::ivec3& b) const noexcept {
            return std::tie(a.x, a.y, a.z) < std::tie(b.x, b.y, b.z);
        }
    };
    template<>
    struct less<BlockPos> {
        inline constexpr bool operator()(const BlockPos& a, const BlockPos& b) const noexcept {
            return std::tie(a.x, a.y, a.z) < std::tie(b.x, b.y, b.z);
        }
    };

    template <typename T>
    inline constexpr auto sincos(T x) {
        return std::pair{std::sin(x), std::cos(x)};
    }

}