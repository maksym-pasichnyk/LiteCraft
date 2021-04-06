#pragma once

#include "../block/BlockData.hpp"

#include <glm/vec3.hpp>

struct BlockReader {
    virtual auto getData(const BlockPos& pos) const -> BlockData = 0;
    virtual auto getBlockLight(const BlockPos& pos) const -> int32_t = 0;

    template <typename Fn>
    bool hasBlockState(const BlockPos& pos, Fn&& fn) {
        return fn(getData(pos));
    }
};
