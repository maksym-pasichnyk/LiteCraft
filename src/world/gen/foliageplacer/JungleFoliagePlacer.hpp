#pragma once

#include "FoliagePlacer.hpp"

struct JungleFoliagePlacer : FoliagePlacer {
    int height;

    JungleFoliagePlacer(FeatureSpread radius, FeatureSpread offset, int height)
        : FoliagePlacer(radius, offset), height(height) {}

    int getHeight(Random &random, int heightIn, const BaseTreeFeatureConfig &config) override {
        return height;
    }

    bool func_230373_a_(Random &random, int p_230373_2_, int p_230373_3_, int p_230373_4_, int radius, bool p_230373_6_) override {
        if ((p_230373_2_ + p_230373_4_) >= 7) {
            return true;
        }
        return (p_230373_2_ * p_230373_2_ + p_230373_4_ * p_230373_4_) > radius * radius;
    }

    void func_230372_a_(WorldGenRegion &reader, Random &random, const BaseTreeFeatureConfig &config, int p_230372_4_, const Foliage &foliage, int p_230372_6_, int p_230372_7_, std::set<BlockPos> &set1, int p_230372_9_, BoundingBox &boundingBox) override {
        const int i = foliage.persistence ? p_230372_6_ : 1 + random.nextInt(2);

        for (int j = p_230372_9_; j >= p_230372_9_ - i; --j) {
            const int k = p_230372_7_ + foliage.distance + 1 - j;
            placeLeaves(reader, random, config, foliage.position, k, set1, j, foliage.persistence, boundingBox);
        }
    }
};