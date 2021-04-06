#include "TopSolidOncePlacement.hpp"
#include "../../WorldGenRegion.hpp"

void TopSolidOncePlacement::forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, BlockPos pos, const std::function<void(BlockPos)> &fn) {
    const int y = region.getHeight(HeightmapType::OCEAN_FLOOR_WG, pos.x, pos.z);
    if (y > 0) {
        fn(BlockPos(pos.x, y, pos.z));
    }
}
