#pragma once

#include "Placement.hpp"

struct SquarePlacement : Placement {
    void forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, BlockPos pos, const std::function<void(BlockPos)> &fn) override {
        const int x = random.nextInt(16) + pos.x;
        const int z = random.nextInt(16) + pos.z;
        fn(BlockPos(x, pos.y, z));
    }
};