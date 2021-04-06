#include "DecoratedPlacement.hpp"
#include "ConfiguredPlacement.hpp"

void DecoratedPlacement::forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, BlockPos pos, const std::function<void(BlockPos)> &fn) {
    const auto& cfg = std::get<DecoratedPlacementConfig>(config);

    cfg.outer->forEach(region, random, pos, [&cfg, &region, &random, &fn](BlockPos pos) {
        cfg.inner->forEach(region, random, pos, fn);
    });
}
