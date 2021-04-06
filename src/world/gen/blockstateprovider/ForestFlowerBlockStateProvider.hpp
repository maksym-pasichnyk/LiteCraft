#pragma once

#include "BlockStateProvider.hpp"

#include <array>

class ForestFlowerBlockStateProvider : BlockStateProvider {
    std::array<BlockData, 11> STATES;

    ForestFlowerBlockStateProvider();
    BlockData getBlockState(Random &random, BlockPos pos) override;
};