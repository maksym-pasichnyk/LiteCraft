#pragma once

#include "Feature.hpp"

struct NetherVegetationFeature : Feature {
    bool generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) override;

    static bool place(WorldGenRegion &reader, Random& random, const BlockPos& pos, const BlockStateProvidingFeatureConfig& config, int xz_range, int y_range);
};