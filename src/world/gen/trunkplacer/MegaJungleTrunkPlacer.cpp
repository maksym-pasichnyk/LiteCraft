#define _USE_MATH_DEFINES

#include "MegaJungleTrunkPlacer.hpp"
#include "../../../util/math/utility.hpp"

std::list<FoliagePlacer::Foliage> MegaJungleTrunkPlacer::getFoliages(WorldGenRegion &reader, Random &random, int height, const BlockPos &pos, std::set<BlockPos> &set1, BoundingBox &boundingBox, const BaseTreeFeatureConfig &config) {
    auto foliages = GiantTrunkPlacer::getFoliages(reader, random, height, pos, set1, boundingBox, config);

    int i = height - 2 - random.nextInt(4);
    for (; i > height / 2; i -= 2 + random.nextInt(4)) {
        const auto [sf, cf] = std::sincos(random.nextFloat() * (static_cast<float>(M_PI) * 2.0F));

        for (int l = 0; l < 5; ++l) {
            const int j = static_cast<int>(1.5F + cf * static_cast<float>(l));
            const int k = static_cast<int>(1.5F + sf * static_cast<float>(l));
            const auto blockpos = pos + BlockPos(j, i - 3 + l / 2, k);
            placeTrunk(reader, random, blockpos, set1, boundingBox, config);
        }

        const int j = static_cast<int>(1.5F + cf * static_cast<float>(4));
        const int k = static_cast<int>(1.5F + sf * static_cast<float>(4));
        foliages.emplace_back(pos + BlockPos(j, i, k), -2, false);
    }

    return foliages;
}
