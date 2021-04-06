#include "ChancePlacement.hpp"

void ChancePlacement::forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, BlockPos pos, const std::function<void(BlockPos)> &fn) {
    const auto& cfg = std::get<ChanceConfig>(config);
    if (random.nextFloat() <= 1.0f / static_cast<float>(cfg.chance)) {
        fn(pos);
    }
}