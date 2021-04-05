#pragma once

#include "FoliagePlacer.hpp"

struct AcaciaFoliagePlacer : FoliagePlacer {
    using FoliagePlacer::FoliagePlacer;

    int getHeight(Random &random, int heightIn, const BaseTreeFeatureConfig& config) override;
    bool func_230373_a_(Random &random, int p_230373_2_, int p_230373_3_, int p_230373_4_, int radius, bool p_230373_6_) override;
    void func_230372_a_(WorldGenRegion &reader, Random &random, const BaseTreeFeatureConfig &config, int p_230372_4_, const Foliage &foliage, int p_230372_6_, int p_230372_7_, std::set<glm::ivec3> &set1, int p_230372_9_, BoundingBox &boundingBox) override;
};