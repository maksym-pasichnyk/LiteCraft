#pragma once

#include "BlobFoliagePlacer.hpp"

struct BushFoliagePlacer : BlobFoliagePlacer {
    using BlobFoliagePlacer::BlobFoliagePlacer;

    bool func_230373_a_(Random &random, int p_230373_2_, int p_230373_3_, int p_230373_4_, int radius, bool p_230373_6_) override {
        return p_230373_2_ == radius && p_230373_4_ == radius && random.nextInt(2) == 0;
    }

    void func_230372_a_(WorldGenRegion &reader, Random &random, const BaseTreeFeatureConfig &config, int p_230372_4_, const Foliage &foliage, int p_230372_6_, int p_230372_7_, std::set<glm::ivec3> &set1, int p_230372_9_, BoundingBox &boundingBox) override {
        for (int i = p_230372_9_; i >= p_230372_9_ - p_230372_6_; --i) {
            const int j = p_230372_7_ + foliage.distance - 1 - i;
            func_236753_a_(reader, random, config, foliage.position, j, set1, i, foliage.persistence, boundingBox);
        }
    }
};