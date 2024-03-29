#include "MegaJungleTrunkPlacer.hpp"
#include "../../../util/math/utility.hpp"

template <typename T>
inline constexpr auto sincos(T x) {
    return std::pair{std::sin(x), std::cos(x)};
}

std::list<FoliagePlacer::Foliage> MegaJungleTrunkPlacer::getFoliages(WorldGenRegion &reader, Random &random, int height, const BlockPos &pos, std::set<BlockPos> &set1, BoundingBox &boundingBox, const BaseTreeFeatureConfig &config) {
    auto foliages = GiantTrunkPlacer::getFoliages(reader, random, height, pos, set1, boundingBox, config);

    int i = height - 2 - random.nextInt(4);
    for (; i > height / 2; i -= 2 + random.nextInt(4)) {
        const auto [sf, cf] = sincos(random.nextFloat() * (static_cast<float>(M_PI) * 2.0F));

        for (int l = 0; l < 5; ++l) {
            const auto j = static_cast<int>(1.5F + cf * static_cast<float>(l));
            const auto k = static_cast<int>(1.5F + sf * static_cast<float>(l));
            const auto blockpos = pos.add(j, i - 3 + l / 2, k);
            placeTrunk(reader, random, blockpos, set1, boundingBox, config);
        }

        const auto j = static_cast<int>(1.5F + cf * static_cast<float>(4));
        const auto k = static_cast<int>(1.5F + sf * static_cast<float>(4));
        foliages.emplace_back(pos.add(j, i, k), -2, false);
    }

    return foliages;
}
