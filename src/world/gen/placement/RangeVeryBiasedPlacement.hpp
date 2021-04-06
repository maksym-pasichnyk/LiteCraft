#pragma once

#include "Placement.hpp"

struct RangeVeryBiasedPlacement : Placement {
    void forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, BlockPos pos, const std::function<void(BlockPos)> &fn) override {
        const auto& cfg = std::get<TopSolidRangeConfig>(config);

        const int y = random.nextInt(random.nextInt(random.nextInt(cfg.maximum - cfg.topOffset) + cfg.bottomOffset + cfg.bottomOffset));

        fn(BlockPos(pos.x, y, pos.z));
    }
};