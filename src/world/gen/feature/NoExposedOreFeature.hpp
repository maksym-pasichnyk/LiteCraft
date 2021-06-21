#pragma once

#include "Feature.hpp"

struct NoExposedOreFeature : Feature {
    bool generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) override;

    static int getRandomOffset(Random& random, int range);

    static bool isFacingAir(WorldGenRegion &reader, const BlockPos& pos);
};