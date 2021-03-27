#pragma once

#include "BlockStateProvider.hpp"

#include <array>

struct PlainFlowerBlockStateProvider : BlockStateProvider {
    std::array<BlockData, 4> RARE_FLOWERS;
    std::array<BlockData, 4> COMMON_FLOWERS;

    PlainFlowerBlockStateProvider();
    BlockData getBlockState(Random &random, glm::ivec3 pos) override;
};