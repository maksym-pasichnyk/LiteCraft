#pragma once

#include "Feature.hpp"

struct IceAndSnowFeature : Feature {
    bool generate(WorldGenRegion& region, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) override;
};