#pragma once

#include "../../../block/BlockData.hpp"

struct Random;
struct BlockStateProvider {
    virtual ~BlockStateProvider() = default;
    virtual BlockData getBlockState(Random& random, BlockPos pos) = 0;
};