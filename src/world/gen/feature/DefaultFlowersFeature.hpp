#pragma once

#include "FlowersFeature.hpp"

struct DefaultFlowersFeature : FlowersFeature {
    bool isValidPosition(WorldGenRegion &reader, glm::ivec3 pos, const BlockClusterFeatureConfig &config) override;
    bool getFlowerCount(const BlockClusterFeatureConfig &config) override;
    glm::ivec3 getNearbyPos(Random &rand, glm::ivec3 pos, const BlockClusterFeatureConfig &config) override;
    BlockData getFlowerToPlace(Random &rand, glm::ivec3 pos, const BlockClusterFeatureConfig &config) override;
};