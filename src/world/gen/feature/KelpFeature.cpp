#include "KelpFeature.hpp"
#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <world/WorldGenRegion.hpp>

bool KelpFeature::generate(WorldGenRegion& reader, ChunkGenerator& generator, Random& random, BlockPos pos, const FeatureConfig& config) {
    int count_of_kelp = 0;
    auto blockpos = reader.getHeight(HeightmapType::OCEAN_FLOOR, pos);
    if (reader.getData(blockpos).is(Blocks::WATER)) {
        const auto KELP = Blocks::KELP->getDefaultState();
        const auto KELP_PLANT = Blocks::KELP_PLANT->getDefaultState();
        const auto height = 1 + random.nextInt(10);

        for (int k = 0; k <= height; ++k) {
            if (reader.getData(blockpos).is(Blocks::WATER) && reader.getData(blockpos.up()).is(Blocks::WATER) && KELP_PLANT.isValidPosition(reader, blockpos)) {
                if (k == height) {
                    const auto age = random.nextInt(4) + 20;
                    reader.setData(blockpos, KELP /*.with<KelpTopBlock.AGE>(age)*//*, 2*/);
                    ++count_of_kelp;
                } else {
                    reader.setData(blockpos, KELP_PLANT /*, 2*/);
                }
            } else if (k > 0) {
                const auto blockpos1 = blockpos.down();
                if (KELP.isValidPosition(reader, blockpos1) && !reader.getData(blockpos1.down()).is(Blocks::KELP)) {
                    const auto age = random.nextInt(4) + 20;
                    reader.setData(blockpos1, KELP /*.with<KelpTopBlock.AGE>(age)*//*, 2*/);
                    ++count_of_kelp;
                }
                break;
            }

            blockpos = blockpos.up();
        }
    }
    return count_of_kelp > 0;
}