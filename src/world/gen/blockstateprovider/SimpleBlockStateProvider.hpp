#pragma once

#include "BlockStateProvider.hpp"

struct SimpleBlockStateProvider : BlockStateProvider {
    BlockData data;

    explicit SimpleBlockStateProvider(BlockData data) : data(data) {}

    BlockData getBlockState(Random &random, glm::ivec3 pos) override {
        return data;
    }
};