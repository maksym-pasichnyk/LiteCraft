#pragma once

#include "Feature.hpp"

struct LakesFeature : Feature {
    BlockData AIR;

    LakesFeature();
    bool generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) override;
};