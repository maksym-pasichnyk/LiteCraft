#pragma once

#include "Feature.hpp"

struct IceAndSnowFeature : Feature {
    void generate(WorldGenRegion& region, ChunkGenerator &generator, Random &rand, glm::ivec3 pos, const FeatureConfig &config) override;
};