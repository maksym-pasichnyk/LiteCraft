#pragma once

#include "FoliagePlacer.hpp"

struct DarkOakFoliagePlacer : FoliagePlacer {
    using FoliagePlacer::FoliagePlacer;

    int getHeight(Random &random, int heightIn, const BaseTreeFeatureConfig &config) override {
        return 4;
    }

    bool func_230373_a_(Random &random, int p_230373_2_, int p_230373_3_, int p_230373_4_, int radius, bool p_230373_6_) override {
        if (p_230373_3_ == -1 && !p_230373_6_) {
            return p_230373_2_ == radius && p_230373_4_ == radius;
        }
        if (p_230373_3_ == 1) {
            return p_230373_2_ + p_230373_4_ > radius * 2 - 2;
        }
        return false;
    }

    void func_230372_a_(WorldGenRegion &reader, Random &random, const BaseTreeFeatureConfig &config, int p_230372_4_, const Foliage &foliage, int p_230372_6_, int p_230372_7_, std::set<BlockPos> &set1, int p_230372_9_, BoundingBox &boundingBox) override {
        const auto blockpos = foliage.position + BlockPos(0, p_230372_9_, 0);
        bool flag = foliage.persistence;
        if (flag) {
            placeLeaves(reader, random, config, blockpos, p_230372_7_ + 2, set1, -1, flag, boundingBox);
            placeLeaves(reader, random, config, blockpos, p_230372_7_ + 3, set1, 0, flag, boundingBox);
            placeLeaves(reader, random, config, blockpos, p_230372_7_ + 2, set1, 1, flag, boundingBox);
            if (random.nextBoolean()) {
                placeLeaves(reader, random, config, blockpos, p_230372_7_, set1, 2, flag, boundingBox);
            }
        } else {
            placeLeaves(reader, random, config, blockpos, p_230372_7_ + 2, set1, -1, flag, boundingBox);
            placeLeaves(reader, random, config, blockpos, p_230372_7_ + 1, set1, 0, flag, boundingBox);
        }
    }

    bool func_230375_b_(Random& random, int p_230375_2_, int p_230375_3_, int p_230375_4_, int p_230375_5_, bool p_230375_6_) override {
        return p_230375_3_ == 0 && p_230375_6_ && (p_230375_2_ == -p_230375_5_ || p_230375_2_ >= p_230375_5_) && (p_230375_4_ == -p_230375_5_ || p_230375_4_ >= p_230375_5_) || FoliagePlacer::func_230375_b_(random, p_230375_2_, p_230375_3_, p_230375_4_, p_230375_5_, p_230375_6_);
    }
};