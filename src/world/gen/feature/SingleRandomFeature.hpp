#pragma once

#include "Feature.hpp"

struct SingleRandomFeature : Feature {
    bool generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, glm::ivec3 pos, const FeatureConfig &config) override;
};