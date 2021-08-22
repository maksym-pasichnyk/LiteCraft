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
    const auto x0 = rand.nextInt(config.xspread);
    const auto x1 = rand.nextInt(config.xspread);
    const auto y0 = rand.nextInt(config.yspread);
    const auto y1 = rand.nextInt(config.yspread);
    const auto z0 = rand.nextInt(config.zspread);
    const auto z1 = rand.nextInt(config.zspread);
    return pos.add(x0 - x1, y0 - y1, z0 - z1);
}

BlockData DefaultFlowersFeature::getFlowerToPlace(Random &rand, BlockPos pos, const BlockClusterFeatureConfig &config) {
    return Blocks::DANDELION->getDefaultState();
}
