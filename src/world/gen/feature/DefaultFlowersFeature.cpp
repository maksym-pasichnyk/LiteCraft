#include "DefaultFlowersFeature.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../../block/Block.hpp"
#include "../../../block/Blocks.hpp"

bool DefaultFlowersFeature::isValidPosition(WorldGenRegion &reader, BlockPos pos, const BlockClusterFeatureConfig &config) {
    return !config.blacklist.contains(reader.getData(pos));
}

int DefaultFlowersFeature::getFlowerCount(const BlockClusterFeatureConfig &config) {
    return config.tries;
}

BlockPos DefaultFlowersFeature::getNearbyPos(Random &rand, BlockPos pos, const BlockClusterFeatureConfig &config) {
    const int x0 = rand.nextInt(config.xspread);
    const int x1 = rand.nextInt(config.xspread);
    const int y0 = rand.nextInt(config.yspread);
    const int y1 = rand.nextInt(config.yspread);
    const int z0 = rand.nextInt(config.zspread);
    const int z1 = rand.nextInt(config.zspread);
    return pos + BlockPos(x0 - x1, y0 - y1, z0 - z1);
}

BlockData DefaultFlowersFeature::getFlowerToPlace(Random &rand, BlockPos pos, const BlockClusterFeatureConfig &config) {
    return Blocks::DANDELION->getDefaultState();
}
