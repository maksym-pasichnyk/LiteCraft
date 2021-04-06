#pragma once

#include "Placement.hpp"

struct DepthAveragePlacement : Placement {
    void forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, BlockPos pos, const std::function<void(BlockPos)> &fn) override {
        const auto& cfg = std::get<DepthAverageConfig>(config);
        const int y = random.nextInt(cfg.spread) + random.nextInt(cfg.spread) - cfg.spread + cfg.baseline;
        fn(BlockPos(pos.x, y, pos.z));
    }
};