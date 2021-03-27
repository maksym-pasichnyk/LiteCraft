#pragma once

#include "Feature.hpp"
#include "../../../block/BlockData.hpp"

struct BlockClusterFeatureConfig;
struct FlowersFeature : Feature {
    virtual bool isValidPosition(WorldGenRegion &reader, glm::ivec3 pos, const BlockClusterFeatureConfig& config) = 0;
    virtual bool getFlowerCount(const BlockClusterFeatureConfig& config) = 0;
    virtual glm::ivec3 getNearbyPos(Random &rand, glm::ivec3 pos, const BlockClusterFeatureConfig& config) = 0;
    virtual BlockData getFlowerToPlace(Random &rand, glm::ivec3 pos, const BlockClusterFeatureConfig& config) = 0;

    bool generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &rand, glm::ivec3 pos, const FeatureConfig &config) override;
};