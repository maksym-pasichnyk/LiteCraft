#pragma once

#include "Feature.hpp"

struct IceAndSnowFeature : Feature {
    bool generate(WorldGenRegion& region, ChunkGenerator &generator, Random &random, glm::ivec3 pos, const FeatureConfig &config) override;
};