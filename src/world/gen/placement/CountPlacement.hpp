#pragma once

#include "Placement.hpp"

struct CountPlacement : Placement {
    void forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, BlockPos pos, const std::function<void(BlockPos)> &fn) override {
        const auto& cfg = std::get<FeatureSpreadConfig>(config);
        const int count = cfg.spread.getCount(random);

        for (int i = 0; i < count; i++) {
            fn(pos);
        }
    }
};