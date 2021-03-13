#pragma once

#include "../../../block/BlockData.hpp"

struct Random;

struct BlockDataProvider {
    virtual BlockData getBlockState(Random& rand, glm::ivec3 blockPos) = 0;
};