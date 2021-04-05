#pragma once

#include "FoliagePlacer.hpp"

struct BlobFoliagePlacer : FoliagePlacer {
    int height;

    BlobFoliagePlacer(FeatureSpread radius, FeatureSpread offset, int height)
        : FoliagePlacer(radius, offset), height(height) {}

    int getHeight(Random &random, int heightIn, const BaseTreeFeatureConfig &config) override {
        return height;
    }

    bool func_230373_a_(Random &random, int p_230373_2_, int p_230373_3_, int p_230373_4_, int radius, bool p_230373_6_) override {
        return p_230373_2_ == radius && p_230373_4_ == radius && (random.nextInt(2) == 0 || p_230373_3_ == 0);
    }

    void func_230372_a_(WorldGenRegion &reader, Random &random, const BaseTreeFeatureConfig &config, int p_230372_4_, const Foliage &foliage, int p_230372_6_, int p_230372_7_, std::set<glm::ivec3> &set1, int p_230372_9_, BoundingBox &boundingBox) override {
        for (int i = p_230372_9_; i >= p_230372_9_ - p_230372_6_; --i) {
            const int j = std::max(p_230372_7_ + foliage.distance - 1 - i / 2, 0);
            func_236753_a_(reader, random, config, foliage.position, j, set1, i, foliage.persistence, boundingBox);
        }
    }
};