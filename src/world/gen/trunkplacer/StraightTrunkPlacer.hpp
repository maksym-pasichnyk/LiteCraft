#pragma once

#include "AbstractTrunkPlacer.hpp"

struct StraightTrunkPlacer : AbstractTrunkPlacer {
    using AbstractTrunkPlacer::AbstractTrunkPlacer;

    std::list<FoliagePlacer::Foliage> getFoliages(WorldGenRegion &reader, Random &random, int height, const BlockPos &pos, std::set<BlockPos> &set1, BoundingBox &boundingBox, const BaseTreeFeatureConfig &config) override;
};