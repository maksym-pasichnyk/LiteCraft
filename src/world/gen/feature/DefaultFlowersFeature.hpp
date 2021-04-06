#pragma once

#include "FlowersFeature.hpp"

struct DefaultFlowersFeature : FlowersFeature {
    bool isValidPosition(WorldGenRegion &reader, BlockPos pos, const BlockClusterFeatureConfig &config) override;
    int getFlowerCount(const BlockClusterFeatureConfig &config) override;
    BlockPos getNearbyPos(Random &rand, BlockPos pos, const BlockClusterFeatureConfig &config) override;
    BlockData getFlowerToPlace(Random &rand, BlockPos pos, const BlockClusterFeatureConfig &config) override;
};