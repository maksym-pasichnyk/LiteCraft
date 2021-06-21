#pragma once

#include "Feature.hpp"

struct ReplaceBlockFeature : Feature {
    bool generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) override;
};