#include "StraightTrunkPlacer.hpp"

std::list<FoliagePlacer::Foliage> StraightTrunkPlacer::getFoliages(WorldGenRegion &reader, Random &random, int height, const glm::ivec3 &pos, std::set<glm::ivec3> &set1, BoundingBox &boundingBox, const BaseTreeFeatureConfig &config) {
    placeDirt(reader, pos - glm::ivec3(0, 1, 0));

    for (int i = 0; i < height; ++i) {
        placeTrunk(reader, random, pos + glm::ivec3(0, i, 0), set1, boundingBox, config);
    }

    return {FoliagePlacer::Foliage(pos + glm::ivec3(0, height, 0), 0, false)};
}
