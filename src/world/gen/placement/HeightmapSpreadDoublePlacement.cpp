#include "HeightmapSpreadDoublePlacement.hpp"
#include "../../WorldGenRegion.hpp"

void HeightmapSpreadDoublePlacement::forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, BlockPos pos, const std::function<void(BlockPos)> &fn) {
    const int y = region.getHeight(HeightmapType::MOTION_BLOCKING, pos.x, pos.z);
    if (y > 0) {
        fn(BlockPos(pos.x, random.nextInt(y * 2), pos.z));
    }
}
