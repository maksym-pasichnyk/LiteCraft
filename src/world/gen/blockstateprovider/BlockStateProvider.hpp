#pragma once

#include "../../../block/BlockData.hpp"

struct Random;
struct BlockStateProvider {
    virtual BlockData getBlockState(Random& random, glm::ivec3 pos) = 0;
};