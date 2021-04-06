#pragma once

#include "Placement.hpp"

struct EndIslandPlacement : Placement {
    void forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, BlockPos pos, const std::function<void(BlockPos)> &fn) override {
        if (random.nextInt(14) == 0) {
            fn(pos + BlockPos(random.nextInt(16), 55 + random.nextInt(16), random.nextInt(16)));
            if (random.nextInt(4) == 0) {
                fn(pos + BlockPos(random.nextInt(16), 55 + random.nextInt(16), random.nextInt(16)));
            }
        }
    }
};