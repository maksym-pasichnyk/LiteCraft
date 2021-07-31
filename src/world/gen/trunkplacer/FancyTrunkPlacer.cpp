#define _USE_MATH_DEFINES

#include "FancyTrunkPlacer.hpp"
#include "../feature/TreeFeature.hpp"
#include "../../WorldGenRegion.hpp"
#include "../blockstateprovider/BlockStateProvider.hpp"
#include "../../../util/math/utility.hpp"

#include <cmath>

std::list<FoliagePlacer::Foliage> FancyTrunkPlacer::getFoliages(WorldGenRegion &reader, Random &random, int height, const BlockPos &pos, std::set<BlockPos> &set1, BoundingBox &boundingBox, const BaseTreeFeatureConfig &config) {
    const int j = height + 2;
    const int k = static_cast<int>(std::floor(static_cast<double>(j) * 0.618));
    if (!config.forcePlacement) {
        placeDirt(reader, pos.down());
    }

    const int l = std::min(1, static_cast<int>(std::floor(1.382 + std::pow(static_cast<double>(j) / 13.0, 2.0))));
    const int i1 = pos.y + k;
    int j1 = j - 5;
    std::list<Foliage> foliages{};
    foliages.emplace_back(pos.up(j1), i1);

    for (; j1 >= 0; --j1) {
        const float f = func_236890_b_(j, j1);
        if (f < 0.0F) {
            continue;
        }
        for (int k1 = 0; k1 < l; ++k1) {
            const double d2 = 1.0 * static_cast<double>(f) * (static_cast<double>(random.nextFloat()) + 0.328);
            const double d3 = static_cast<double>(random.nextFloat() * 2.0F) * M_PI;
            const double d4 = d2 * std::sin(d3) + 0.5;
            const double d5 = d2 * std::cos(d3) + 0.5;
            const BlockPos blockpos = pos + BlockPos(d4, j1 - 1, d5);
            const auto blockpos1 = blockpos.up(5);
            if (placeTrunk(reader, random, blockpos, blockpos1, false, set1, boundingBox, config)) {
                const int dx = pos.x - blockpos.x;
                const int dz = pos.z - blockpos.z;
                const double d6 = static_cast<double>(blockpos.y) - std::sqrt(dx * dx + dz * dz) * 0.381;
                const int j2 = d6 > static_cast<double>(i1) ? i1 : static_cast<int>(d6);
                const BlockPos blockpos2{pos.x, j2, pos.z};
                if (placeTrunk(reader, random, blockpos2, blockpos, false, set1, boundingBox, config)) {
                    foliages.emplace_back(blockpos, blockpos2.y);
                }
            }
        }
    }

    placeTrunk(reader, random, pos, pos.up(k), true, set1, boundingBox, config);
    func_236886_a_(reader, random, j, pos, foliages, set1, boundingBox, config);
    std::list<FoliagePlacer::Foliage> list1{};
    for (const auto& foliage : foliages) {
        if (func_236885_a_(j, foliage.y - pos.y)) {
            list1.emplace_back(foliage.foliage);
        }
    }
    return list1;
}

bool FancyTrunkPlacer::placeTrunk(WorldGenRegion &reader, Random& random, const BlockPos &pos1, const BlockPos &pos2, bool needPlace, std::set<BlockPos> &set1, BoundingBox &boundingBox, const BaseTreeFeatureConfig &config) {
    if (!needPlace && (pos1 == pos2)) {
        return true;
    }
    const auto blockpos = pos2 - pos1;
    const int i = lMaxNorm(blockpos);
    const auto[f, f1, f2] = glm::vec3(blockpos) / static_cast<float>(i);

    for (int j = 0; j <= i; ++j) {
        const auto blockpos1 = glm::vec3(pos1) + glm::vec3(0.5F + (float)j * f, 0.5F + (float)j * f1, 0.5F + (float)j * f2);
        if (needPlace) {
            const auto state = config.trunkProvider->getBlockState(random, blockpos1);
//                    .with(RotatedPillarBlock::AXIS, func_236889_a_(pos1, blockpos1));
            placeBlockState(reader, blockpos1, state, boundingBox);
            set1.emplace(blockpos1);
        } else if (!TreeFeature::isReplaceableOrLogAt(reader, blockpos1)) {
            return false;
        }
    }

    return true;
}
