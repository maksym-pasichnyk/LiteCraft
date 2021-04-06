#pragma once

#include "AbstractTrunkPlacer.hpp"

struct GiantTrunkPlacer : AbstractTrunkPlacer {
    using AbstractTrunkPlacer::AbstractTrunkPlacer;

    std::list<FoliagePlacer::Foliage> getFoliages(WorldGenRegion &reader, Random &random, int heightIn, const BlockPos &pos, std::set<BlockPos> &set1, BoundingBox &boundingBox, const BaseTreeFeatureConfig &config) override;
};