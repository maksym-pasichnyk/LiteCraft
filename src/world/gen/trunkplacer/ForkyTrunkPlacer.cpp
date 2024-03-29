#include "ForkyTrunkPlacer.hpp"
#include "../../../util/Direction.hpp"

std::list<FoliagePlacer::Foliage> ForkyTrunkPlacer::getFoliages(WorldGenRegion &reader, Random &random, int height, const BlockPos &pos, std::set<BlockPos> &set1, BoundingBox &boundingBox, const BaseTreeFeatureConfig &config) {
    placeDirt(reader, pos.down());
    std::list<FoliagePlacer::Foliage> foliages{};
    const auto direction = random.nextElement(std::span(DirectionUtil::Plane::HORIZONTAL));
    const int i = height - random.nextInt(4) - 1;

    {
        auto [k, l] = std::pair{pos.x, pos.z};
        int j = 3 - random.nextInt(3);
        int i1 = 0;

        for (int j1 = 0; j1 < height; ++j1) {
            const int k1 = pos.y + j1;
            if (j1 >= i && j > 0) {
                k += DirectionUtil::getXOffset(direction);
                l += DirectionUtil::getZOffset(direction);
                --j;
            }

            if (placeTrunk(reader, random, BlockPos(k, k1, l), set1, boundingBox, config)) {
                i1 = k1 + 1;
            }
        }

        foliages.emplace_back(BlockPos(k, i1, l), 1, false);
    }

    const auto direction1 = random.nextElement(std::span(DirectionUtil::Plane::HORIZONTAL));
    if (direction1 != direction) {
        auto [k, l] = std::pair{pos.x, pos.z};
        const int k2 = i - random.nextInt(2) - 1;
        int l1 = 1 + random.nextInt(3);
        int i1 = 0;

        for (int i2 = k2; i2 < height && l1 > 0; --l1) {
            if (i2 >= 1) {
                const int j2 = pos.y + i2;
                k += DirectionUtil::getXOffset(direction1);
                l += DirectionUtil::getZOffset(direction1);
                if (placeTrunk(reader, random, BlockPos(k, j2, l), set1, boundingBox, config)) {
                    i1 = j2 + 1;
                }
            }

            ++i2;
        }

        if (i1 > 1) {
            foliages.emplace_back(BlockPos(k, i1, l), 0, false);
        }
    }

    return foliages;
}