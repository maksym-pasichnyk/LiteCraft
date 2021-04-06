#include "LakeWaterPlacement.hpp"
#include "../../WorldGenRegion.hpp"

void LakeWaterPlacement::forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, BlockPos pos, const std::function<void(BlockPos)> &fn) {
    const auto& cfg = std::get<ChanceConfig>(config);

    if (random.nextInt(cfg.chance) == 0) {
        const int x = random.nextInt(16) + pos.x;
        const int z = random.nextInt(16) + pos.z;
        const int y = random.nextInt(region.getMaxBuildHeight());
        fn(BlockPos(x, y, z));
    }
}
