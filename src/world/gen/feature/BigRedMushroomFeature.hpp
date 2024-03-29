#pragma once

#include "AbstractBigMushroomFeature.hpp"

struct BigRedMushroomFeature : AbstractBigMushroomFeature {
    int func_225563_a_(int p_225563_1_, int p_225563_2_, int p_225563_3_, int p_225563_4_) override;

    void generateCap(WorldGenRegion &reader, Random &random, const BlockPos &pos, int height, const BigMushroomFeatureConfig &config) override;
};