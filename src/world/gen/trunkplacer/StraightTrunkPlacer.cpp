#include "StraightTrunkPlacer.hpp"

std::list<FoliagePlacer::Foliage> StraightTrunkPlacer::getFoliages(WorldGenRegion &reader, Random &random, int height, const BlockPos &pos, std::set<BlockPos> &set1, BoundingBox &boundingBox, const BaseTreeFeatureConfig &config) {
    placeDirt(reader, pos.down());

    for (int i = 0; i < height; ++i) {
        placeTrunk(reader, random, pos.up(i), set1, boundingBox, config);
    }

    return {FoliagePlacer::Foliage(pos.up(height), 0, false)};
}
