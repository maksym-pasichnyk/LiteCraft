#include "IcebergFeature.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../../block/Block.hpp"
#include "../../../block/Blocks.hpp"
#include "../../../block/material/Materials.hpp"

#include <ranges>
#include <algorithm>

int IcebergFeature::func_205178_b(int a, int b, int c) {
    const float f1 = (1.0F - static_cast<float>(std::pow(a, 2.0)) / (static_cast<float>(b) * 1.0F)) * static_cast<float>(c);
    return static_cast<int>(std::ceil(f1 / 2.0F));
}

int IcebergFeature::func_205183_a(Random &random, int a, int b, int c) {
    const float f1 = [&random, a, b, c] {
        const float f = 3.5F - random.nextFloat();
        if (b > 15 + random.nextInt(5)) {
            const int i = a < 3 + random.nextInt(6) ? a / 2 : a;
            return (1.0F - static_cast<float>(i) / (static_cast<float>(b) * f * 0.4F)) * static_cast<float>(c);
        } else {
            return (1.0F - static_cast<float>(std::pow(a, 2.0)) / (static_cast<float>(b) * f)) * static_cast<float>(c);
        }
    }();
    return static_cast<int>(std::ceil(f1 / 2.0F));
}

void IcebergFeature::func_205181_a(WorldGenRegion &region, Random &random, const BlockPos &pos, int e, int x, int y, int z, int a, int b, bool flag, int c, double d, bool flag2, BlockData state) {
    const double d0 = flag
                      ? func_205180_a(x, z, BlockPos{}, b, func_205176_a(y, e, c), d)
                      : func_205177_a(x, z, BlockPos{}, a, random);
    if (d0 < 0.0) {
        const double d1 = flag ? -0.5 : (double)(-6 - random.nextInt(3));
        if (d0 > d1 && random.nextDouble() > 0.9) {
            return;
        }

        const auto blockpos = pos + glm::ivec3(x, y, z);
        func_205175_a(blockpos, region, random, e - y, e, flag, flag2, state);
    }
}

double IcebergFeature::func_205180_a(int x, int z, const BlockPos& pos, int a, int b, double c) {
    const auto f0 = static_cast<double>(x - pos.x) * std::cos(c) - static_cast<double>(z - pos.z) * std::sin(c);
    const auto f1 = static_cast<double>(x - pos.x) * std::sin(c) + static_cast<double>(z - pos.z) * std::cos(c);
    return std::pow(f0 / static_cast<double>(a), 2.0) + std::pow(f1 / static_cast<double>(b), 2.0) - 1.0;
}

int IcebergFeature::func_205176_a(int a, int b, int c) {
    return (a > 0 && (b - a) <= 3) ? (c - (4 - (b - a))) : c;
}

double IcebergFeature::func_205177_a(int a, int b, const BlockPos &pos, int c, Random &random) {
    const float f = 10.0F * std::clamp(random.nextFloat(), 0.2F, 0.8F) / static_cast<float>(c);
    return static_cast<double>(f) + std::pow(a - pos.x, 2) + std::pow(b - pos.z, 2) - std::pow(c, 2);
}

void IcebergFeature::func_205175_a(const BlockPos &pos, WorldGenRegion &region, Random &random, int a, int b, bool p_205175_6_, bool p_205175_7_, BlockData p_205175_8_) {
    const auto blockstate = region.getData(pos);
    if (blockstate.getMaterial() == Materials::AIR ||
        blockstate.is(Blocks::SNOW_BLOCK) ||
        blockstate.is(Blocks::ICE) ||
        blockstate.is(Blocks::WATER)) {
        const bool flag = !p_205175_6_ || random.nextDouble() > 0.05;
        const int i = p_205175_6_ ? 3 : 2;
        if (p_205175_7_ && !blockstate.is(Blocks::WATER) && static_cast<double>(a) <= static_cast<double>(random.nextInt(std::max(1, b / i))) + static_cast<double>(b) * 0.6 && flag) {
            setBlockState(region, pos, Blocks::SNOW_BLOCK->getDefaultState());
        } else {
            setBlockState(region, pos, p_205175_8_);
        }
    }

}

int IcebergFeature::func_205187_b(Random &random, int a, int b, int c) {
    const float f = 1.0F + random.nextFloat() / 2.0F;
    const float f1 = (1.0F - static_cast<float>(a) / (static_cast<float>(b) * f)) * static_cast<float>(c);
    return static_cast<int>(std::ceil(f1 / 2.0F));
}

void IcebergFeature::func_205186_a(WorldGenRegion &region, const BlockPos &pos, int a, int b, bool flag, int d) {
    const int i = flag ? d : (a / 2);

    const auto AIR = Blocks::AIR->getDefaultState();

    for (int j = -i; j <= i; ++j) {
        for (int k = -i; k <= i; ++k) {
            for(int l = 0; l <= b; ++l) {
                const BlockPos blockpos = pos + glm::ivec3(j, l, k);
                const auto block = region.getData(blockpos).getBlock();
                if (isIce(block) || block == Blocks::SNOW) {
                    if (isAirBellow(region, blockpos)) {
                        setBlockState(region, blockpos, AIR);
                        setBlockState(region, blockpos.up(), AIR);
                    } else if (isIce(block)) {
                        const std::array blocks {
                            region.getData(blockpos.west()).getBlock(),
                            region.getData(blockpos.east()).getBlock(),
                            region.getData(blockpos.north()).getBlock(),
                            region.getData(blockpos.south()).getBlock()
                        };
                        if (std::ranges::count_if(blocks, isIce) >= 3) {
                            setBlockState(region, blockpos, AIR);
                        }
                    }
                }
            }
        }
    }
}

bool IcebergFeature::isIce(Block* block) {
    return block == Blocks::PACKED_ICE || block == Blocks::SNOW_BLOCK || block == Blocks::BLUE_ICE;
}

bool IcebergFeature::isAirBellow(WorldReader &reader, const BlockPos &pos) {
    return reader.getData(pos.down()).getMaterial() == Materials::AIR;
}

void IcebergFeature::func_205184_a(Random &random, WorldGenRegion &region, int a, int b, const BlockPos &pos, bool flag, int c, double d, int e) {
    const int i = random.nextBoolean() ? -1 : 1;
    const int j = random.nextBoolean() ? -1 : 1;
    int k = random.nextInt(std::max(a / 2 - 2, 1));
    if (random.nextBoolean()) {
        k = a / 2 + 1 - random.nextInt(std::max(a - a / 2 - 1, 1));
    }

    int l = random.nextInt(std::max(a / 2 - 2, 1));
    if (random.nextBoolean()) {
        l = a / 2 + 1 - random.nextInt(std::max(a - a / 2 - 1, 1));
    }

    if (flag) {
        k = l = random.nextInt(std::max(c - 5, 1));
    }

    const BlockPos blockpos{i * k, 0, j * l};
    const double d0 = flag
            ? (d + (M_PI / 2.0))
            : (random.nextDouble() * 2.0 * M_PI);

    for (int i1 = 0; i1 < b - 3; ++i1) {
        const int j1 = func_205183_a(random, i1, b, a);
        func_205174_a(j1, i1, pos, region, false, d0, blockpos, c, e);
    }

    for (int k1 = -1; k1 > -b + random.nextInt(5); --k1) {
        const int l1 = func_205187_b(random, -k1, b, a);
        func_205174_a(l1, k1, pos, region, true, d0, blockpos, c, e);
    }
}

void IcebergFeature::func_205174_a(int p_205174_1_, int yDiff, const BlockPos& p_205174_3_, WorldGenRegion &region, bool placeWater, double p_205174_6_, const BlockPos& p_205174_8_, int p_205174_9_, int p_205174_10_) {
    const auto AIR = Blocks::AIR->getDefaultState();
    const auto WATER = Blocks::WATER->getDefaultState();

    const int i = p_205174_1_ + 1 + p_205174_9_ / 3;
    const int j = std::min(p_205174_1_ - 3, 3) + p_205174_10_ / 2 - 1;

    for (int k = -i; k < i; ++k) {
        for (int l = -i; l < i; ++l) {
            const double d0 = func_205180_a(k, l, p_205174_8_, i, j, p_205174_6_);
            if (d0 < 0.0) {
                const auto blockpos = p_205174_3_ + glm::ivec3(k, yDiff, l);
                const auto block = region.getData(blockpos).getBlock();
                if (isIce(block) || block == Blocks::SNOW_BLOCK) {
                    if (placeWater) {
                        setBlockState(region, blockpos, WATER);
                    } else {
                        setBlockState(region, blockpos, AIR);
                        removeSnowLayer(region, blockpos);
                    }
                }
            }
        }
    }
}

void IcebergFeature::removeSnowLayer(WorldGenRegion &region, const BlockPos& pos) {
    if (region.getData(pos.up()).is(Blocks::SNOW)) {
        setBlockState(region, pos.up(), Blocks::AIR->getDefaultState());
    }
}

bool IcebergFeature::generate(WorldGenRegion &region, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto& cfg = std::get<SphereReplaceConfig>(config);
    const bool flag = random.nextDouble() > 0.7;
    const auto state = cfg.state;
    const double d0 = random.nextDouble() * 2.0 * M_PI;
    const int i = 11 - random.nextInt(5);
    const int j = 3 + random.nextInt(3);
    const bool flag1 = random.nextDouble() > 0.7;
    int l = flag1
            ? (random.nextInt(6) + 6)
            : (random.nextInt(15) + 3);
    if (!flag1 && random.nextDouble() > 0.9) {
        l += random.nextInt(19) + 7;
    }

    pos.y = region.getSeaLevel();

    const int i1 = std::min(l + random.nextInt(11), 18);
    const int g0 = random.nextInt(7);
    const int g1 = random.nextInt(5);
    const int j1 = std::min(l + g0 - g1, 11);
    const int k1 = flag1 ? i : 11;

    for (int l1 = -k1; l1 < k1; ++l1) {
        for (int i2 = -k1; i2 < k1; ++i2) {
            for (int j2 = 0; j2 < l; ++j2) {
                const int k2 = flag1 ? func_205178_b(j2, l, j1) : func_205183_a(random, j2, l, j1);
                if (flag1 || l1 < k2) {
                    func_205181_a(region, random, pos, l, l1, j2, i2, k2, k1, flag1, j, d0, flag, state);
                }
            }
        }
    }

    func_205186_a(region, pos, j1, l, flag1, i);

    for (int i3 = -k1; i3 < k1; ++i3) {
        for (int j3 = -k1; j3 < k1; ++j3) {
            for (int k3 = -1; k3 > -i1; --k3) {
                const int l3 = flag1
                               ? static_cast<int>(std::ceil(static_cast<float>(k1) * (1.0F - static_cast<float>(std::pow(k3, 2.0)) / (static_cast<float>(i1) * 8.0F))))
                               : k1;
                const int l2 = func_205187_b(random, -k3, i1, j1);
                if (i3 < l2) {
                    func_205181_a(region, random, pos, i1, i3, k3, j3, l2, l3, flag1, j, d0, flag, state);
                }
            }
        }
    }

    const bool flag2 = flag1
            ? (random.nextDouble() > 0.1)
            : (random.nextDouble() > 0.7);
    if (flag2) {
        func_205184_a(random, region, j1, l, pos, flag1, i, d0, j);
    }
    return true;
}