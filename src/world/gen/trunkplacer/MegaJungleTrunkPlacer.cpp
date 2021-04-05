#include "MegaJungleTrunkPlacer.hpp"

std::list<FoliagePlacer::Foliage> MegaJungleTrunkPlacer::getFoliages(WorldGenRegion &reader, Random &random, int height, const glm::ivec3 &pos, std::set<glm::ivec3> &set1, BoundingBox &boundingBox, const BaseTreeFeatureConfig &config) {
    auto foliages = GiantTrunkPlacer::getFoliages(reader, random, height, pos, set1, boundingBox, config);

    for (int i = height - 2 - random.nextInt(4); i > height / 2; i -= 2 + random.nextInt(4)) {
        const float f = random.nextFloat() * (static_cast<float>(M_PI) * 2.0F);

        const auto [sf, cf] = std::pair{std::sin(f), std::cos(f)};

        for (int l = 0; l < 5; ++l) {
            const int j = static_cast<int>(1.5F + cf * static_cast<float>(l));
            const int k = static_cast<int>(1.5F + sf * static_cast<float>(l));
            const auto blockpos = pos + glm::ivec3(j, i - 3 + l / 2, k);
            placeTrunk(reader, random, blockpos, set1, boundingBox, config);
        }

        const int j = static_cast<int>(1.5F + cf * static_cast<float>(4));
        const int k = static_cast<int>(1.5F + sf * static_cast<float>(4));
        foliages.emplace_back(pos + glm::ivec3(j, i, k), -2, false);
    }

    return foliages;
}
