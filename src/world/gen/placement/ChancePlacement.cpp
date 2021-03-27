#include "ChancePlacement.hpp"

void ChancePlacement::forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, glm::ivec3 pos, const std::function<void(glm::ivec3)> &fn) {
    const auto& cfg = std::get<ChanceConfig>(config);
    if (random.nextFloat() <= 1.0f / static_cast<float>(cfg.chance)) {
        fn(pos);
    }
}