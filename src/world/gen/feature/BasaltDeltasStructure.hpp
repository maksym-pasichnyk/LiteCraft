#pragma once

#include "Feature.hpp"
#include <set>

struct BasaltDeltasStructure : Feature {
    static std::set<Block*> blacklist;

    BasaltDeltasStructure();

    bool generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) override;
    
    static bool func_236277_a_(WorldGenRegion &reader, BlockPos pos, const BasaltDeltasFeature& config);
};