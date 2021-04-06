#pragma once

#include "Feature.hpp"

struct BambooFeature : Feature {
    BlockData BAMBOO;
    BlockData BAMBOO_BASE;
    BlockData BAMBOO_LARGE_LEAVES_GROWN;
    BlockData BAMBOO_LARGE_LEAVES;
    BlockData BAMBOO_SMALL_LEAVES;

    BambooFeature();
    bool generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) override;
};