#pragma once

#include "../block/BlockData.hpp"

#include <glm/vec3.hpp>

struct BlockReader {
    virtual auto getData(const glm::ivec3& pos) const -> BlockData = 0;
    virtual auto getBlockLight(const glm::ivec3& pos) const -> int32_t = 0;

    template <typename Fn>
    bool hasBlockState(const glm::ivec3& pos, Fn&& fn) {
        return fn(getData(pos));
    }
};
