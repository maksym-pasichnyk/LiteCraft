#include "AbstractBigMushroomFeature.hpp"
#include "../blockstateprovider/BlockStateProvider.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../../block/Block.hpp"

bool AbstractBigMushroomFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto& cfg = std::get<BigMushroomFeatureConfig>(config);

    const int height = getStemHeight(random);
    if (!checkPosition(reader, pos, height, cfg)) {
        return false;
    }
    generateCap(reader, random, pos, height, cfg);
    generateStem(reader, random, pos, cfg, height);
    return true;
}

void AbstractBigMushroomFeature::generateStem(WorldGenRegion &world, Random &random, const BlockPos &pos, const BigMushroomFeatureConfig &config, int height) {
    for (int i = 0; i < height; ++i) {
        const auto blockpos = pos + BlockPos(0, i, 0);
        if (!world.getData(blockpos).isOpaque() /*isOpaqueCube(world, mutpos)*/) {
            world.setData(blockpos, config.stemProvider->getBlockState(random, pos)/*, 3*/);
        }
    }
}

int AbstractBigMushroomFeature::getStemHeight(Random &random) {
    int i = random.nextInt(3) + 4;
    if (random.nextInt(12) == 0) {
        i *= 2;
    }
    return i;
}

bool AbstractBigMushroomFeature::checkPosition(WorldGenRegion &world, const BlockPos &pos, int height, const BigMushroomFeatureConfig &config) {
    const int starty = pos.y;
    if (starty >= 1 && starty + height + 1 < 256) {
        auto block = world.getData(pos.down()).getBlock();
        if (!isDirt(block) && !block->isIn(BlockTags::MUSHROOM_GROW_BLOCK)) {
            return false;
        }
        for (int j = 0; j <= height; ++j) {
            const int k = func_225563_a_(-1, -1, config.foliageRadius, j);

            for (int l = -k; l <= k; ++l) {
                for (int i1 = -k; i1 <= k; ++i1) {
                    const auto state = world.getData(pos + BlockPos(l, j, i1));
                    if (!state.isAir() && !state.in(BlockTags::LEAVES)) {
                        return false;
                    }
                }
            }
        }

        return true;
    }
    return false;
}
