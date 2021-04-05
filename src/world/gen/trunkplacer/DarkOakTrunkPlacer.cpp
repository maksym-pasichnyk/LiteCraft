#include "DarkOakTrunkPlacer.hpp"
#include "../feature/TreeFeature.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../../util/Direction.hpp"

std::list<FoliagePlacer::Foliage> DarkOakTrunkPlacer::getFoliages(WorldGenRegion &reader, Random &random, int heightIn, const glm::ivec3 &pos, std::set<glm::ivec3> &set1, BoundingBox &boundingBox, const BaseTreeFeatureConfig &config) {
    std::list<FoliagePlacer::Foliage> list{};
    const auto blockpos = pos - glm::ivec3(0, 1, 0);
    placeDirt(reader, blockpos);
    placeDirt(reader, blockpos + glm::ivec3(1, 0, 0));
    placeDirt(reader, blockpos + glm::ivec3(0, 0, 1));
    placeDirt(reader, blockpos + glm::ivec3(1, 0, 1));
    const auto direction = random.nextElement(std::span(Directions::Plane::HORIZONTAL));
    const int i = heightIn - random.nextInt(4);
    int j = 2 - random.nextInt(3);
    const int xStart = pos.x;
    const int yStart = pos.y;
    const int zStart = pos.z;
    int xPos = xStart;
    int zPos = zStart;
    const int yPos = yStart + heightIn - 1;

    for(int i2 = 0; i2 < heightIn; ++i2) {
        if (i2 >= i && j > 0) {
            xPos += Directions::getXOffset(direction);
            zPos += Directions::getZOffset(direction);
            --j;
        }

        const glm::ivec3 blockpos1{xPos, yStart + i2, zPos};
        if (TreeFeature::isAirOrLeavesAt(reader, blockpos1)) {
            placeTrunk(reader, random, blockpos1, set1, boundingBox, config);
            placeTrunk(reader, random, blockpos1 + glm::ivec3(1, 0, 0), set1, boundingBox, config);
            placeTrunk(reader, random, blockpos1 + glm::ivec3(0, 0, 1), set1, boundingBox, config);
            placeTrunk(reader, random, blockpos1 + glm::ivec3(1, 0, 1), set1, boundingBox, config);
        }
    }

    list.emplace_back(glm::ivec3(xPos, yPos, zPos), 0, true);

    for(int x = -1; x <= 2; ++x) {
        for(int z = -1; z <= 2; ++z) {
            if ((x < 0 || x > 1 || z < 0 || z > 1) && random.nextInt(3) <= 0) {
                const int randHeight = random.nextInt(3) + 2;

                for(int y = 0; y < randHeight; ++y) {
                    placeTrunk(reader, random, glm::ivec3(xStart + x, yPos - y - 1, zStart + z), set1, boundingBox, config);
                }

                list.emplace_back(glm::ivec3(xPos + x, yPos, zPos + z), 0, false);
            }
        }
    }

    return list;
}
