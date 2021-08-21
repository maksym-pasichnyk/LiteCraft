#include "IceAndSnowFeature.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../biome/Biome.hpp"
#include "../../../block/Block.hpp"
#include "../../../block/Blocks.hpp"
#include "../../../block/SnowyDirtBlock.hpp"

bool IceAndSnowFeature::generate(WorldGenRegion& region, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    for (int x = 0; x < 16; x++) {
        for (int z = 0; z < 16; z++) {
            const int xpos = pos.x + x;
            const int zpos = pos.z + z;
            const int ypos = region.getHeight(HeightmapType::MOTION_BLOCKING, xpos, zpos);
            const BlockPos blockpos1{xpos, ypos, zpos};
            const BlockPos blockpos2{xpos, ypos - 1, zpos};
            auto biome = region.getBiome(blockpos1);
            if (biome->doesWaterFreeze(region, blockpos2, false)) {
                region.setData(blockpos2, Blocks::ICE->getDefaultState()/*, 2*/);
            }

            if (biome->doesSnowGenerate(region, blockpos1)) {
                region.setData(blockpos1, Blocks::SNOW->getDefaultState()/*, 2*/);
                const auto state = region.getData(blockpos2);
                if (state.has(SnowyDirtBlock::SNOWY)) {
//                    region.setData(blockpos2, state.set<SnowyDirtBlock::SNOWY>(true)/*, 2*/);
                }
            }
        }
    }
    return true;
}
