#pragma once

#include "Feature.hpp"

struct BasaltPillarFeature : Feature {
    bool generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) override;

    static void placeBasalt(WorldGenRegion &reader, Random& random, const BlockPos& pos);
    static bool placeBasaltRandom10(WorldGenRegion &reader, Random& random, const BlockPos& pos);
};