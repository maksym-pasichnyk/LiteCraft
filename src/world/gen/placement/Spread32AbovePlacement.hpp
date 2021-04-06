#pragma once

#include "Placement.hpp"

struct Spread32AbovePlacement : Placement {
    void forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, BlockPos pos, const std::function<void(BlockPos)> &fn) override {
        const int y = random.nextInt(pos.y + 32);
        fn(BlockPos(pos.x, y, pos.z));
    }
};