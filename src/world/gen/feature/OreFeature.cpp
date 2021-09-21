#include "OreFeature.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../../block/Blocks.hpp"

#include <cmath>
#include <algorithm>

bool OreFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto& cfg = std::get<OreFeatureConfig>(config);
    
    const float f = random.nextFloat() * static_cast<float>(M_PI);
    const float f1 = static_cast<float>(cfg.size) / 8.0F;
    const int i = static_cast<int>(std::ceil((static_cast<float>(cfg.size) / 16.0F * 2.0F + 1.0F) / 2.0F));
    const double d0 = pos.x + std::sin(f) * f1;
    const double d1 = pos.x - std::sin(f) * f1;
    const double d2 = pos.z + std::cos(f) * f1;
    const double d3 = pos.z - std::cos(f) * f1;
    const double d4 = pos.y + random.nextInt(3) - 2;
    const double d5 = pos.y + random.nextInt(3) - 2;
    const int k = pos.x - static_cast<int>(std::ceil(f1)) - i;
    const int l = pos.y - 2 - i;
    const int i1 = pos.z - static_cast<int>(std::ceil(f1)) - i;
    const int j1 = 2 * (static_cast<int>(std::ceil(f1)) + i);
    const int k1 = 2 * (2 + i);

    for(int l1 = k; l1 <= k + j1; ++l1) {
        for(int i2 = i1; i2 <= i1 + j1; ++i2) {
            if (l <= reader.getHeight(HeightmapType::OCEAN_FLOOR_WG, l1, i2)) {
                return generateOre(reader, random, cfg, d0, d1, d2, d3, d4, d5, k, l, i1, j1, k1);
            }
        }
    }
    return false;
}

bool OreFeature::generateOre(WorldGenRegion &world, Random &random, const OreFeatureConfig &config, double p_207803_4_, double p_207803_6_, double p_207803_8_, double p_207803_10_, double p_207803_12_, double p_207803_14_, int p_207803_16_, int p_207803_17_, int p_207803_18_, int sizex, int sizey) {
    std::vector<bool> mask(sizex * sizey * sizex);

    const int size = config.size;
    std::vector<double> doubles(size * 4);

    for (int k = 0; k < size; ++k) {
        const float f = static_cast<float>(k) / static_cast<float>(size);
        const double d0 = std::lerp(p_207803_4_, p_207803_6_, static_cast<double>(f));
        const double d2 = std::lerp(p_207803_12_, p_207803_14_, static_cast<double>(f));
        const double d4 = std::lerp(p_207803_8_, p_207803_10_, static_cast<double>(f));
        const double d6 = random.nextDouble() * static_cast<double>(size) / 16.0;
        const double d7 = (static_cast<double>(std::sin(static_cast<float>(M_PI) * f) + 1.0F) * d6 + 1.0) / 2.0;
        doubles[k * 4 + 0] = d0;
        doubles[k * 4 + 1] = d2;
        doubles[k * 4 + 2] = d4;
        doubles[k * 4 + 3] = d7;
    }

    for (int i3 = 0; i3 < size - 1; ++i3) {
        if (doubles[i3 * 4 + 3] <= 0.0) {
            continue;
        }
        for (int k3 = i3 + 1; k3 < size; ++k3) {
            if (doubles[k3 * 4 + 3] <= 0.0) {
                continue;
            }
            const double d12 = doubles[i3 * 4 + 0] - doubles[k3 * 4 + 0];
            const double d13 = doubles[i3 * 4 + 1] - doubles[k3 * 4 + 1];
            const double d14 = doubles[i3 * 4 + 2] - doubles[k3 * 4 + 2];
            const double d15 = doubles[i3 * 4 + 3] - doubles[k3 * 4 + 3];
            if (d15 * d15 > d12 * d12 + d13 * d13 + d14 * d14) {
                if (d15 > 0.0) {
                    doubles[k3 * 4 + 3] = -1.0;
                } else {
                    doubles[i3 * 4 + 3] = -1.0;
                }
            }
        }
    }

    int i = 0;
    for (int j3 = 0; j3 < size; ++j3) {
        const double d11 = doubles[j3 * 4 + 3];
        if (d11 < 0.0) {
            continue;
        }
        const double d1 = doubles[j3 * 4 + 0];
        const double d3 = doubles[j3 * 4 + 1];
        const double d5 = doubles[j3 * 4 + 2];
        const int l = std::max(static_cast<int>(std::floor(d1 - d11)), p_207803_16_);
        const int l3 = std::max(static_cast<int>(std::floor(d3 - d11)), p_207803_17_);
        const int i1 = std::max(static_cast<int>(std::floor(d5 - d11)), p_207803_18_);
        const int j1 = std::max(static_cast<int>(std::floor(d1 + d11)), l);
        const int k1 = std::max(static_cast<int>(std::floor(d3 + d11)), l3);
        const int l1 = std::max(static_cast<int>(std::floor(d5 + d11)), i1);

        for (int i2 = l; i2 <= j1; ++i2) {
            const double d8 = (static_cast<double>(i2) + 0.5 - d1) / d11;
            if ((d8 * d8) >= 1.0) {
                continue;
            }
            for (int j2 = l3; j2 <= k1; ++j2) {
                const double d9 = (static_cast<double>(j2) + 0.5 - d3) / d11;
                if ((d8 * d8 + d9 * d9) >= 1.0) {
                    continue;
                }
                for (int k2 = i1; k2 <= l1; ++k2) {
                    const double d10 = (static_cast<double>(k2) + 0.5 - d5) / d11;
                    if (d8 * d8 + d9 * d9 + d10 * d10 < 1.0) {
                        const int l2 = i2 - p_207803_16_ + (j2 - p_207803_17_) * sizex + (k2 - p_207803_18_) * sizex * sizey;
                        if (!mask[l2]) {
                            mask[l2] = true;

                            if (RuleTestUtil::test(config.target, world.getData(i2, j2, k2), random)) {
                                world.setData(i2, j2, k2, config.state/*, 2*/);
                                ++i;
                            }
                        }
                    }
                }
            }
        }
    }

    return i > 0;
}