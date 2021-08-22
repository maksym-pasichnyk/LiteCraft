#include "BigBrownMushroomFeature.hpp"
#include "../blockstateprovider/BlockStateProvider.hpp"
#include "../../WorldGenRegion.hpp"
#include <block/HugeMushroomBlock.hpp>

int BigBrownMushroomFeature::func_225563_a_(int p_225563_1_, int p_225563_2_, int p_225563_3_, int p_225563_4_) {
    return p_225563_4_ <= 3 ? 0 : p_225563_3_;
}

void BigBrownMushroomFeature::generateCap(WorldGenRegion &reader, Random &random, const BlockPos &pos, int height, const BigMushroomFeatureConfig &config) {
    const auto radius = config.foliageRadius;

    for (int dx = -radius; dx <= radius; ++dx) {
        for (int dz = -radius; dz <= radius; ++dz) {
            const auto flag0 = dx == -radius;
            const auto flag1 = dx == radius;
            const auto flag2 = dz == -radius;
            const auto flag3 = dz == radius;
            const auto flag4 = flag0 || flag1;
            const auto flag5 = flag2 || flag3;
            if (flag4 && flag5) {
                continue;
            }
            const auto blockpos = pos.add(dx, height, dz);
            if (!reader.getData(blockpos).isOpaque()/*isOpaqueCube(reader, blockpos)*/) {
                const auto state = config.capProvider->getBlockState(random, pos)
                    .set<HugeMushroomBlock::WEST>(flag0 || flag5 && dx == 1 - radius)
                    .set<HugeMushroomBlock::EAST>(flag1 || flag5 && dx == radius - 1)
                    .set<HugeMushroomBlock::NORTH>(flag2 || flag4 && dz == 1 - radius)
                    .set<HugeMushroomBlock::SOUTH>(flag3 || flag4 && dz == radius - 1);
                reader.setData(blockpos, state/*, 3*/);
            }
        }
    }
}
