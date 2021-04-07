#include "BlockWithContextFeature.hpp"
#include "../../WorldGenRegion.hpp"

bool BlockWithContextFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto& cfg = std::get<BlockWithContextConfig>(config);
    if (cfg.placeOn.contains(reader.getData(pos.down())) && cfg.placeIn.contains(reader.getData(pos)) && cfg.placeUnder.contains(reader.getData(pos.up()))) {
        reader.setData(pos, cfg.toPlace/*, 2*/);
        return true;
    }
    return false;
}
