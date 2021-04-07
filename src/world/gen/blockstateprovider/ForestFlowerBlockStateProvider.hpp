#pragma once

#include "BlockStateProvider.hpp"

#include <array>

struct ForestFlowerBlockStateProvider : BlockStateProvider {
    std::array<BlockData, 11> STATES;

    ForestFlowerBlockStateProvider();
    BlockData getBlockState(Random &random, BlockPos pos) override;
};