#pragma once

#include "../block/BlockData.hpp"

#include <glm/vec3.hpp>

struct BlockReader {
    virtual auto getData(glm::ivec3 pos) const -> BlockData = 0;
    virtual auto getBlockLight(glm::ivec3 pos) const -> int32_t = 0;
};
