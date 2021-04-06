#pragma once

#include "../feature/FeatureSpread.hpp"
#include "../../../util/math/BlockPos.hpp"

#include <set>
#include <cmath>

struct Random;
struct BoundingBox;
struct WorldGenRegion;
struct BaseTreeFeatureConfig;
struct FoliagePlacer {
    struct Foliage {
        BlockPos position;
        int distance;
        bool persistence;

        Foliage(const BlockPos& position, int distance, bool persistence) : position(position), distance(distance), persistence(persistence) {}
    };

    FeatureSpread radius;
    FeatureSpread offset;

    FoliagePlacer(FeatureSpread radius, FeatureSpread offset) : radius(radius), offset(offset) {}
    virtual ~FoliagePlacer() = default;

    void func_236752_a_(WorldGenRegion& reader, Random& random, const BaseTreeFeatureConfig& config, int p_236752_4_, const Foliage& foliage, int p_236752_6_, int p_236752_7_, std::set<BlockPos>& set1, BoundingBox& boundingBox) {
        func_230372_a_(reader, random, config, p_236752_4_, foliage, p_236752_6_, p_236752_7_, set1, getOffset(random), boundingBox);
    }

    void placeLeaves(WorldGenRegion& reader, Random& random, const BaseTreeFeatureConfig& config, const BlockPos& pos, int p_236753_5_, std::set<BlockPos>& set1, int height, bool p_236753_8_, BoundingBox& boundingBox);

    virtual int getRadius(Random& random, int p_230376_2_) {
        return radius.getCount(random);
    }

    virtual int getOffset(Random& p_236755_1_) {
        return offset.getCount(p_236755_1_);
    }

    virtual bool func_230375_b_(Random& random, int p_230375_2_, int p_230375_3_, int p_230375_4_, int p_230375_5_, bool flag) {
        int i;
        int j;
        if (flag) {
            i = std::min(std::abs(p_230375_2_), std::abs(p_230375_2_ - 1));
            j = std::min(std::abs(p_230375_4_), std::abs(p_230375_4_ - 1));
        } else {
            i = std::abs(p_230375_2_);
            j = std::abs(p_230375_4_);
        }

        return func_230373_a_(random, i, p_230375_3_, j, p_230375_5_, flag);
    }

    virtual int getHeight(Random& random, int heightIn, const BaseTreeFeatureConfig& config) = 0;
    virtual bool func_230373_a_(Random& random, int p_230373_2_, int p_230373_3_, int p_230373_4_, int radius, bool p_230373_6_) = 0;
    virtual void func_230372_a_(WorldGenRegion& reader, Random& random, const BaseTreeFeatureConfig& config, int p_230372_4_, const Foliage& foliage, int p_230372_6_, int p_230372_7_, std::set<BlockPos>& set1, int p_230372_9_, BoundingBox& boundingBox) = 0;
};