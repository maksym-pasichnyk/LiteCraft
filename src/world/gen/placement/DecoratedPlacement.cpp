#include "DecoratedPlacement.hpp"
#include "ConfiguredPlacement.hpp"

void DecoratedPlacement::forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, glm::ivec3 pos, const std::function<void(glm::ivec3)> &fn) {
    const auto& cfg = std::get<DecoratedPlacementConfig>(config);

    cfg.outer->forEach(region, random, pos, [&cfg, &region, &random, &fn](glm::ivec3 pos) {
        cfg.inner->forEach(region, random, pos, fn);
    });
}
