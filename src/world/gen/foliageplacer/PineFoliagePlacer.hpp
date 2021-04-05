#pragma once

#include "FoliagePlacer.hpp"

struct PineFoliagePlacer : FoliagePlacer {
    FeatureSpread spread;
    PineFoliagePlacer(FeatureSpread radius, FeatureSpread offset, FeatureSpread spread) : FoliagePlacer(radius, offset), spread(spread) {}

    int getRadius(Random& random, int p_230376_2_) override {
        return FoliagePlacer::getRadius(random, p_230376_2_) + random.nextInt(p_230376_2_ + 1);
    }

    int getHeight(Random &random, int heightIn, const BaseTreeFeatureConfig &config) override {
        return spread.getCount(random);
    }

    bool func_230373_a_(Random &random, int p_230373_2_, int p_230373_3_, int p_230373_4_, int radius, bool p_230373_6_) override {
        return p_230373_2_ == radius && p_230373_4_ == radius && radius > 0;
    }

    void func_230372_a_(WorldGenRegion &reader, Random &random, const BaseTreeFeatureConfig &config, int p_230372_4_, const Foliage &foliage, int p_230372_6_, int p_230372_7_, std::set<glm::ivec3> &set1, int p_230372_9_, BoundingBox &boundingBox) override {
        int i = 0;
        for (int j = p_230372_9_; j >= p_230372_9_ - p_230372_6_; --j) {
            func_236753_a_(reader, random, config, foliage.position, i, set1, j, foliage.persistence, boundingBox);
            if (i >= 1 && j == p_230372_9_ - p_230372_6_ + 1) {
                --i;
            } else if (i < p_230372_7_ + foliage.distance) {
                ++i;
            }
        }
    }
};