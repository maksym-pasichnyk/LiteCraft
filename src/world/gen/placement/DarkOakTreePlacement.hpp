#pragma once

#include "Placement.hpp"

struct DarkOakTreePlacement : Placement {
    void forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, BlockPos pos, const std::function<void(BlockPos)> &fn) override;
};