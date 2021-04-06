#include "DarkOakTreePlacement.hpp"
#include "../../WorldGenRegion.hpp"

void DarkOakTreePlacement::forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, BlockPos pos, const std::function<void(BlockPos)> &fn) {
    for (int i = 0; i < 16; i++) {
        const int x = (i / 4) * 4 + 1 + random.nextInt(3) + pos.x;
        const int z = (i % 4) * 4 + 1 + random.nextInt(3) + pos.z;
        const int y = region.getHeight(HeightmapType::MOTION_BLOCKING, x, z);
        fn(BlockPos(x, y, z));
    }
}
