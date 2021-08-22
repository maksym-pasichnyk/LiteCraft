#include "BigRedMushroomFeature.hpp"
#include "../blockstateprovider/BlockStateProvider.hpp"
#include "../../WorldGenRegion.hpp"
#include <block/HugeMushroomBlock.hpp>

int BigRedMushroomFeature::func_225563_a_(int p_225563_1_, int p_225563_2_, int p_225563_3_, int p_225563_4_) {
    if (p_225563_4_ < p_225563_2_ && p_225563_4_ >= p_225563_2_ - 3) {
        return p_225563_3_;
    }
    if (p_225563_4_ == p_225563_2_) {
        return p_225563_3_;
    }
    return 0;
}

void BigRedMushroomFeature::generateCap(WorldGenRegion &reader, Random &random, const BlockPos &pos, int height, const BigMushroomFeatureConfig &config) {
    const auto cap_radius = config.foliageRadius - 2;
    for (int dy = height - 3; dy <= height; ++dy) {
        const auto radius = dy < height ? config.foliageRadius : config.foliageRadius - 1;

        for (int dx = -radius; dx <= radius; ++dx) {
            for (int dz = -radius; dz <= radius; ++dz) {
                const auto flag0 = dx == -radius;
                const auto flag1 = dx == radius;
                const auto flag2 = dz == -radius;
                const auto flag3 = dz == radius;
                const auto flag4 = flag0 || flag1;
                const auto flag5 = flag2 || flag3;
                if (dy >= height || flag4 != flag5) {
                    const auto blockpos = pos.add(dx, dy, dz);
                    if (!reader.getData(blockpos).isOpaque()/*isOpaqueCube(reader, blockpos)*/) {
                        const auto state = config.capProvider->getBlockState(random, pos)
                            .set<HugeMushroomBlock::UP>(dy >= height - 1)
                            .set<HugeMushroomBlock::WEST>(dx < -cap_radius)
                            .set<HugeMushroomBlock::EAST>(dx > cap_radius)
                            .set<HugeMushroomBlock::NORTH>(dz < -cap_radius)
                            .set<HugeMushroomBlock::SOUTH>(dz > cap_radius);
                        reader.setData(blockpos, state/*, 3*/);
                    }
                }
            }
        }
    }
}
