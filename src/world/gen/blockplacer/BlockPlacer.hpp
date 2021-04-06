#pragma once

struct Random;
struct WorldGenRegion;

struct BlockPlacer {
    virtual ~BlockPlacer() = default;
    virtual void place(WorldGenRegion& world, BlockPos pos, BlockData blockData, Random& rand) = 0;
};