#pragma once

#include "Placement.hpp"

struct IcebergPlacement : Placement {
    void forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, BlockPos pos, const std::function<void(BlockPos)> &fn) override {
        const int x = random.nextInt(8) + 4 + pos.x;
        const int y = random.nextInt(8) + 4 + pos.z;
        fn(BlockPos(x, pos.y, y));
    }
};