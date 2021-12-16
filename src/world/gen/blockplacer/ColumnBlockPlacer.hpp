#pragma once

#include "BlockPlacer.hpp"
#include "../../WorldGenRegion.hpp"

#include <spdlog/spdlog.h>

struct ColumnBlockPlacer : public BlockPlacer {
    int minSize;
    int extraSize;

    ColumnBlockPlacer(int minSize, int extraSize) : minSize(minSize), extraSize(extraSize) {}

    void place(WorldGenRegion &world, BlockPos pos, BlockData state, Random &random) override {
        const int height = minSize + random.nextInt(random.nextInt(extraSize + 1) + 1);
        for (int y = 0; y < height; ++y) {
            world.setData(pos.x, pos.y + y, pos.z, state/*, 2*/);
        }
    }
};