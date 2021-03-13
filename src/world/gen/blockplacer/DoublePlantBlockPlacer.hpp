#pragma once

#include "BlockPlacer.hpp"
#include "../../../WorldGenRegion.hpp"

struct DoublePlantBlockPlacer : public BlockPlacer {
    void place(WorldGenRegion &world, glm::ivec3 pos, BlockData blockData, Random &rand) override {
//        const int height = minSize + rand.nextInt(rand.nextInt(extraSize + 1) + 1);
//        for (int y = 0; y < height; ++y) {
//            world.setData(pos.x, pos.y + y, pos.z, blockData/*, 2*/);
//        }
    }
};