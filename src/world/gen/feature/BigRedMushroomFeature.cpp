#include "BigRedMushroomFeature.hpp"
#include "../blockstateprovider/BlockStateProvider.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../../block/Block.hpp"

int BigRedMushroomFeature::func_225563_a_(int p_225563_1_, int p_225563_2_, int p_225563_3_, int p_225563_4_) {
    int i = 0;
    if (p_225563_4_ < p_225563_2_ && p_225563_4_ >= p_225563_2_ - 3) {
        i = p_225563_3_;
    } else if (p_225563_4_ == p_225563_2_) {
        i = p_225563_3_;
    }
    return i;
}

void BigRedMushroomFeature::generateCap(WorldGenRegion &reader, Random &random, const BlockPos &pos, int height, const BigMushroomFeatureConfig &config) {
    const int k = config.foliageRadius - 2;
    for (int i = height - 3; i <= height; ++i) {
        const int j = i < height ? config.foliageRadius : config.foliageRadius - 1;

        for (int l = -j; l <= j; ++l) {
            for (int i1 = -j; i1 <= j; ++i1) {
                const bool flag = l == -j;
                const bool flag1 = l == j;
                const bool flag2 = i1 == -j;
                const bool flag3 = i1 == j;
                const bool flag4 = flag || flag1;
                const bool flag5 = flag2 || flag3;
                if (i >= height || flag4 != flag5) {
                    const auto blockpos = pos + BlockPos(l, i, i1);
                    if (!reader.getData(blockpos).isOpaque()/*isOpaqueCube(reader, blockpos)*/) {
                        const auto state = config.capProvider->getBlockState(random, pos);
//                        .with(HugeMushroomBlock.UP, i >= height - 1)
//                        .with(HugeMushroomBlock.WEST, l < -k)
//                        .with(HugeMushroomBlock.EAST, l > k)
//                        .with(HugeMushroomBlock.NORTH, i1 < -k)
//                        .with(HugeMushroomBlock.SOUTH, i1 > k);
                        reader.setData(blockpos, state/*, 3*/);
                    }
                }
            }
        }
    }
}
