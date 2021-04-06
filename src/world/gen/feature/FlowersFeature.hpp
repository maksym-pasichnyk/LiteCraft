#pragma once

#include "Feature.hpp"
#include "../../../block/BlockData.hpp"

struct BlockClusterFeatureConfig;
struct FlowersFeature : Feature {
    virtual bool isValidPosition(WorldGenRegion &reader, BlockPos pos, const BlockClusterFeatureConfig& config) = 0;
    virtual int getFlowerCount(const BlockClusterFeatureConfig& config) = 0;
    virtual BlockPos getNearbyPos(Random &rand, BlockPos pos, const BlockClusterFeatureConfig& config) = 0;
    virtual BlockData getFlowerToPlace(Random &rand, BlockPos pos, const BlockClusterFeatureConfig& config) = 0;

    bool generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &rand, BlockPos pos, const FeatureConfig &config) override;
};