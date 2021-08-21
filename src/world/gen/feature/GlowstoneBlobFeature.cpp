#include "GlowstoneBlobFeature.hpp"
#include <world/WorldGenRegion.hpp>
#include <block/Blocks.hpp>
#include <block/Block.hpp>

bool GlowstoneBlobFeature::generate(WorldGenRegion& reader, ChunkGenerator& generator, Random& random, BlockPos pos, const FeatureConfig& config) {
    if (!reader.isAirBlock(pos)) {
        return false;
    }

    const auto state = reader.getData(pos.up());
    if (!state.is(Blocks::NETHERRACK) && !state.is(Blocks::BASALT) && !state.is(Blocks::BLACKSTONE)) {
        return false;
    }
    
    const auto GLOWSTONE = Blocks::GLOWSTONE->getDefaultState();

    reader.setData(pos, GLOWSTONE/*, 2*/);

    for (int i = 0; i < 1500; ++i) {
        const auto dx0 = random.nextInt(8);
        const auto dx1 = random.nextInt(8);
        const auto dy0 = random.nextInt(12);
        const auto dz0 = random.nextInt(8);
        const auto dz1 = random.nextInt(8);

        const auto blockpos = pos.sub(dx1 - dx0, dy0, dz1 - dz0);
        if (reader.getData(blockpos).isAir()) {
            int count_of_blocks = 0;

            for (const auto direction : DirectionUtil::values()) {
                if (reader.getData(blockpos.offset(direction)).is(Blocks::GLOWSTONE)) {
                    ++count_of_blocks;
                }

                if (count_of_blocks > 1) {
                    break;
                }
            }

            if (count_of_blocks == 1) {
                reader.setData(blockpos, GLOWSTONE /*, 2*/);
            }
        }
    }
    return true;
}