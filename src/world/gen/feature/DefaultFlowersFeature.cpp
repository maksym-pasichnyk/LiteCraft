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
    return pos + BlockPos(
        rand.nextInt(config.xspread) - rand.nextInt(config.xspread),
        rand.nextInt(config.yspread) - rand.nextInt(config.yspread),
        rand.nextInt(config.zspread) - rand.nextInt(config.zspread)
    );
}

BlockData DefaultFlowersFeature::getFlowerToPlace(Random &rand, BlockPos pos, const BlockClusterFeatureConfig &config) {
    return Blocks::DANDELION->getDefaultState();
}
