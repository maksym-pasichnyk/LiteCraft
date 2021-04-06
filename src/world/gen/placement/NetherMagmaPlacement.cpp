#include "NetherMagmaPlacement.hpp"
#include "../../WorldGenRegion.hpp"

void NetherMagmaPlacement::forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, BlockPos pos, const std::function<void(BlockPos)> &fn) {
    const int seaLevel = 63;
    const int y = seaLevel - 5 + random.nextInt(10);
    fn(BlockPos(pos.x, y, pos.z));
}
