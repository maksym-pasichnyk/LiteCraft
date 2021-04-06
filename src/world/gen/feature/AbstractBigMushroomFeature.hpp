#pragma once

#include "Feature.hpp"

struct AbstractBigMushroomFeature : Feature {
    bool generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) override;

    void generateStem(WorldGenRegion& world, Random& random, const BlockPos& pos, const BigMushroomFeatureConfig& config, int height);
    int getStemHeight(Random& random);

    bool checkPosition(WorldGenRegion& world, const BlockPos& pos, int height, const BigMushroomFeatureConfig& config);

    virtual int func_225563_a_(int p_225563_1_, int p_225563_2_, int p_225563_3_, int p_225563_4_) = 0;
    virtual void generateCap(WorldGenRegion &reader, Random &random, const BlockPos& pos, int height, const BigMushroomFeatureConfig& config) = 0;
};