#include "IceAndSnowFeature.hpp"
#include "../../../block/Block.hpp"
#include "../../../block/Blocks.hpp"
#include "../../../block/SnowyDirtBlock.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../biome/Biome.hpp"

bool IceAndSnowFeature::generate(WorldGenRegion& region, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    for (int x = 0; x < 16; x++) {
        for (int z = 0; z < 16; z++) {
            const auto top_pos = region.getHeight(HeightmapType::MOTION_BLOCKING, pos.add(x, 0, z));
            const auto down_pos = top_pos.down();
            const auto biome = region.getBiome(top_pos);

            if (biome->doesWaterFreeze(region, down_pos, false)) {
                region.setData(down_pos, Blocks::ICE->getDefaultState()/*, 2*/);
            }

            if (biome->doesSnowGenerate(region, top_pos)) {
                region.setData(top_pos, Blocks::SNOW->getDefaultState()/*, 2*/);
                const auto state = region.getData(down_pos);
                if (state.has(SnowyDirtBlock::SNOWY)) {
                    region.setData(down_pos, state.set<SnowyDirtBlock::SNOWY>(true)/*, 2*/);
                }
            }
        }
    }
    return true;
}
