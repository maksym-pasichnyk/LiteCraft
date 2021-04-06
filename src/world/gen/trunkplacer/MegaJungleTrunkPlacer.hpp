#pragma once

#include "GiantTrunkPlacer.hpp"

struct MegaJungleTrunkPlacer : GiantTrunkPlacer {
    using GiantTrunkPlacer::GiantTrunkPlacer;

    std::list<FoliagePlacer::Foliage> getFoliages(WorldGenRegion &reader, Random &random, int height, const BlockPos &pos, std::set<BlockPos> &set1, BoundingBox &boundingBox, const BaseTreeFeatureConfig &config) override;
};