#pragma once

#include "Feature.hpp"

struct OreFeature : Feature {
    bool generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) override;
    bool generateOre(WorldGenRegion &world, Random& random, const OreFeatureConfig& config, double p_207803_4_, double p_207803_6_, double p_207803_8_, double p_207803_10_, double p_207803_12_, double p_207803_14_, int p_207803_16_, int p_207803_17_, int p_207803_18_, int sizex, int sizey);
};