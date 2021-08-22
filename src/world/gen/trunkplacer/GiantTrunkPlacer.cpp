#include "GiantTrunkPlacer.hpp"

std::list<FoliagePlacer::Foliage> GiantTrunkPlacer::getFoliages(WorldGenRegion &reader, Random &random, int heightIn, const BlockPos &pos, std::set<BlockPos> &set1, BoundingBox &boundingBox, const BaseTreeFeatureConfig &config) {
    const auto blockpos = pos.down();

    placeDirt(reader, blockpos);
    placeDirt(reader, blockpos.east());
    placeDirt(reader, blockpos.south());
    placeDirt(reader, blockpos.south().east());

    for (int i = 0; i < heightIn; ++i) {
        tryPlaceTrunk(reader, random, pos.up(i), set1, boundingBox, config);
        if (i < heightIn - 1) {
            tryPlaceTrunk(reader, random, pos.add(1, i, 0), set1, boundingBox, config);
            tryPlaceTrunk(reader, random, pos.add(1, i, 1), set1, boundingBox, config);
            tryPlaceTrunk(reader, random, pos.add(0, i, 1), set1, boundingBox, config);
        }
    }
    
    return {FoliagePlacer::Foliage(pos.up(heightIn), 0, true)};
}