#pragma once

#include "BlockStateProvider.hpp"
#include "../../../block/Block.hpp"

struct Block;
struct AxisRotatingBlockStateProvider : BlockStateProvider {
    Block* block;

    explicit AxisRotatingBlockStateProvider(Block* block) : block(block) {}

    BlockData getBlockState(Random &random, BlockPos pos) override {
        return block->getDefaultState();
    }
};