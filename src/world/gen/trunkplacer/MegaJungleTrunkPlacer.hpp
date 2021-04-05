#pragma once

#include "GiantTrunkPlacer.hpp"

struct MegaJungleTrunkPlacer : GiantTrunkPlacer {
    using GiantTrunkPlacer::GiantTrunkPlacer;

    std::list<FoliagePlacer::Foliage> getFoliages(WorldGenRegion &reader, Random &random, int height, const glm::ivec3 &pos, std::set<glm::ivec3> &set1, BoundingBox &boundingBox, const BaseTreeFeatureConfig &config) override;
};