#include "FlowersFeature.hpp"
#include "../../WorldGenRegion.hpp"

bool FlowersFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &rand, BlockPos pos, const FeatureConfig &config) {
    const auto& cfg = std::get<BlockClusterFeatureConfig>(config);
    const auto flower = getFlowerToPlace(rand, pos, cfg);
    const int count = getFlowerCount(cfg);

    int i = 0;
    for (int j = 0; j < count; ++j) {
        const auto blockpos = getNearbyPos(rand, pos, cfg);
        if (blockpos.y > 0 && blockpos.y < 255 && reader.isAirBlock(blockpos) && flower.isValidPosition(reader, blockpos) && isValidPosition(reader, blockpos, cfg)) {
            reader.setData(blockpos, flower/*, 2*/);
            ++i;
        }
    }
    return i > 0;
}
