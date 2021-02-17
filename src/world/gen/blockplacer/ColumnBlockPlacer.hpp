#pragma once

#include "BlockPlacer.hpp"

class ColumnBlockPlacer : public BlockPlacer {
    int minSize;
    int extraSize;

public:
    ColumnBlockPlacer(int minSize, int extraSize) : minSize(minSize), extraSize(extraSize) {}

    void place(WorldGenRegion &world, glm::ivec3 pos, BlockData blockData, Random &rand) override {
        const int height = minSize + rand.nextInt(rand.nextInt(extraSize + 1) + 1);
        for (int y = 0; y < height; ++y) {
            world.setData(pos.x, pos.y + y, pos.z, blockData);
        }
    }
};