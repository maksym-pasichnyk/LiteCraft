#include "IcePathFeature.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../../block/Blocks.hpp"

bool IcePathFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    while (reader.isAirBlock(pos) && pos.y > 2) {
        pos.y -= 1;
    }

    return reader.getData(pos).isIn(Blocks::SNOW_BLOCK)
        && AbstractSphereReplaceFeature::generate(reader, generator, random, pos, config);
}
