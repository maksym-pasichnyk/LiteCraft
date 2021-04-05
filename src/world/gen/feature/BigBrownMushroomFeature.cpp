#include "BigBrownMushroomFeature.hpp"
#include "../blockstateprovider/BlockStateProvider.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../../block/Block.hpp"

int BigBrownMushroomFeature::func_225563_a_(int p_225563_1_, int p_225563_2_, int p_225563_3_, int p_225563_4_) {
    return p_225563_4_ <= 3 ? 0 : p_225563_3_;
}

void BigBrownMushroomFeature::generateCap(WorldGenRegion &reader, Random &random, const glm::ivec3 &pos, int height, const BigMushroomFeatureConfig &config) {
    const int radius = config.foliageRadius;

    for (int j = -radius; j <= radius; ++j) {
        for (int k = -radius; k <= radius; ++k) {
            const bool flag = j == -radius;
            const bool flag1 = j == radius;
            const bool flag2 = k == -radius;
            const bool flag3 = k == radius;
            const bool flag4 = flag || flag1;
            const bool flag5 = flag2 || flag3;
            if (flag4 && flag5) {
                continue;
            }
            const auto blockpos = pos + glm::ivec3(j, height, k);
            if (!reader.getData(blockpos).isOpaque()/*isOpaqueCube(reader, blockpos)*/) {
                const auto state = config.capProvider->getBlockState(random, pos);
//                    .with(HugeMushroomBlock.WEST, flag || flag5 && j == 1 - radius)
//                    .with(HugeMushroomBlock.EAST, flag1 || flag5 && j == radius - 1)
//                    .with(HugeMushroomBlock.NORTH, flag2 || flag4 && k == 1 - radius)
//                    .with(HugeMushroomBlock.SOUTH, flag3 || flag4 && k == radius - 1);
                reader.setData(blockpos, state/*, 3*/);
            }
        }
    }
}
