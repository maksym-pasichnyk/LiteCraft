#pragma once

#include "BlockStateProvider.hpp"
#include "../../../block/BlockData.hpp"
#include "../../../util/WeightedList.hpp"

struct WeightedBlockStateProvider : BlockStateProvider {
    WeightedList<BlockData> states;

    WeightedBlockStateProvider(WeightedList<BlockData> states) : states(std::move(states)) {}

    BlockData getBlockState(Random &random, BlockPos pos) override {
        return states.get(random);
    }
};