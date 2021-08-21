#pragma once

#include "Feature.hpp"

struct WeepingVineFeature : Feature {
    bool generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) override;

    void generateWartBlocks(WorldGenRegion &reader, Random &random, const BlockPos& pos);
    void generateVines(WorldGenRegion &reader, Random &random, const BlockPos& pos);

    static void placeVines(WorldGenRegion &reader, Random& random, const BlockPos& start, int height, int min_age, int max_age);
};