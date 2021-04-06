#pragma once

#include "FoliagePlacer.hpp"

struct MegaPineFoliagePlacer : FoliagePlacer {
    FeatureSpread spread;
    MegaPineFoliagePlacer(FeatureSpread radius, FeatureSpread offset, FeatureSpread spread) : FoliagePlacer(radius, offset), spread(spread) {}

    int getHeight(Random &random, int heightIn, const BaseTreeFeatureConfig &config) override {
        return spread.getCount(random);
    }

    bool func_230373_a_(Random &random, int p_230373_2_, int p_230373_3_, int p_230373_4_, int radius, bool p_230373_6_) override {
        if ((p_230373_2_ + p_230373_4_) >= 7) {
            return true;
        }
        return (p_230373_2_ * p_230373_2_ + p_230373_4_ * p_230373_4_) > radius * radius;
    }

    void func_230372_a_(WorldGenRegion &reader, Random &random, const BaseTreeFeatureConfig &config, int p_230372_4_, const Foliage &foliage, int p_230372_6_, int p_230372_7_, std::set<BlockPos> &set1, int p_230372_9_, BoundingBox &boundingBox) override {
        const auto blockpos = foliage.position;
        int i = 0;

        for (int j = blockpos.y - p_230372_6_ + p_230372_9_; j <= blockpos.y + p_230372_9_; ++j) {
            const int k = blockpos.y - j;
            const int l = p_230372_7_ + foliage.distance + static_cast<int>(std::floor((float)k / (float)p_230372_6_ * 3.5F));
            const int i1 = k > 0 && l == i && (j & 1) == 0 ? (l + 1) : l;

            placeLeaves(reader, random, config, BlockPos(blockpos.x, j, blockpos.z), i1, set1, 0, foliage.persistence,
                        boundingBox);
            i = l;
        }
    }
};