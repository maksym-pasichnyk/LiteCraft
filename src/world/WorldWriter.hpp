#pragma once

#include "../block/BlockData.hpp"

struct WorldWriter {
    virtual void setData(const glm::ivec3& pos, BlockData state) = 0;
};