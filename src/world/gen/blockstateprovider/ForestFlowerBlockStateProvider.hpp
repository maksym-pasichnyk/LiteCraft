#pragma once

#include "BlockStateProvider.hpp"

#include <array>

class ForestFlowerBlockStateProvider : BlockStateProvider {
    std::array<BlockData, 11> STATES;

    ForestFlowerBlockStateProvider();
    BlockData getBlockState(Random &random, glm::ivec3 pos) override;
};