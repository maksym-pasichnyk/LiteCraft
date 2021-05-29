#pragma once

#include "Placement.hpp"

struct EndIslandPlacement : Placement {
    void forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, BlockPos pos, const std::function<void(BlockPos)> &fn) override {
        if (random.nextInt(14) == 0) {
            const int dx = random.nextInt(16);
            const int dy = random.nextInt(16);
            const int dz = random.nextInt(16);
            fn(pos + BlockPos(dx, 55 + dy, dz));
            if (random.nextInt(4) == 0) {
                const int dx = random.nextInt(16);
                const int dy = random.nextInt(16);
                const int dz = random.nextInt(16);

                fn(pos + BlockPos(dx, 55 + dy, dz));
            }
        }
    }
};