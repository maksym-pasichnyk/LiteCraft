#pragma once

#include "BlockPlacer.hpp"
#include "../../WorldGenRegion.hpp"

struct SimpleBlockPlacer : public BlockPlacer {
    void place(WorldGenRegion &world, BlockPos pos, BlockData blockData, Random &rand) override {
        world.setData(pos.x, pos.y, pos.z, blockData/*, 2*/);
    }
};