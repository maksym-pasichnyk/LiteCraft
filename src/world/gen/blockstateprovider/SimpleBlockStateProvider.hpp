#pragma once

#include "BlockStateProvider.hpp"

struct SimpleBlockStateProvider : BlockStateProvider {
    BlockData data;

    explicit SimpleBlockStateProvider(BlockData data) : data(data) {}

    BlockData getBlockState(Random &random, BlockPos pos) override {
        return data;
    }
};