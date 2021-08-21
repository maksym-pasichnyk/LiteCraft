#include "ChorusPlantFeature.hpp"
#include <block/Blocks.hpp>
#include <world/WorldGenRegion.hpp>

bool ChorusPlantFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    if (reader.isAirBlock(pos) && reader.getData(pos.down()).is(Blocks::END_STONE)) {
//        ChorusFlowerBlock.generatePlant(reader, pos, rand, 8);
        return true;
    }
    return false;
}