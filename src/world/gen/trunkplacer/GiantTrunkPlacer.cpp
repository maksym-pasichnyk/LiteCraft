#include "GiantTrunkPlacer.hpp"

std::list<FoliagePlacer::Foliage> GiantTrunkPlacer::getFoliages(WorldGenRegion &reader, Random &random, int heightIn, const glm::ivec3 &pos, std::set<glm::ivec3> &set1, BoundingBox &boundingBox, const BaseTreeFeatureConfig &config) {
    const auto blockpos = pos - glm::ivec3(0, 1, 0);

    placeDirt(reader, blockpos);
    placeDirt(reader, blockpos + glm::ivec3(1, 0, 0));
    placeDirt(reader, blockpos + glm::ivec3(0, 0, 1));
    placeDirt(reader, blockpos + glm::ivec3(1, 0, 1));

    for (int i = 0; i < heightIn; ++i) {
        tryPlaceTrunk(reader, random, pos + glm::ivec3(0, i, 0), set1, boundingBox, config);
        if (i < heightIn - 1) {
            tryPlaceTrunk(reader, random, pos + glm::ivec3(1, i, 0), set1, boundingBox, config);
            tryPlaceTrunk(reader, random, pos + glm::ivec3(1, i, 1), set1, boundingBox, config);
            tryPlaceTrunk(reader, random, pos + glm::ivec3(0, i, 1), set1, boundingBox, config);
        }
    }
    
    return {FoliagePlacer::Foliage(pos + glm::ivec3(0, heightIn, 0), 0, true)};
}