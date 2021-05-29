#pragma once

#include "Placement.hpp"

struct DepthAveragePlacement : Placement {
    void forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, BlockPos pos, const std::function<void(BlockPos)> &fn) override {
        const auto& cfg = std::get<DepthAverageConfig>(config);
        const int y0 = random.nextInt(cfg.spread);
        const int y1 = random.nextInt(cfg.spread);
        const int y = y0 + y1 - cfg.spread + cfg.baseline;
        fn(BlockPos(pos.x, y, pos.z));
    }
};