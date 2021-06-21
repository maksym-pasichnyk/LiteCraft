#include "ReplaceBlockFeature.hpp"
#include "world/WorldGenRegion.hpp"

bool ReplaceBlockFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto& cfg = std::get<ReplaceBlockConfig>(config);
    if (reader.getData(pos).is(cfg.target.getBlock())) {
        reader.setData(pos, cfg.state/*, 2*/);
    }
    return false;
}
