#pragma once

#include "Placement.hpp"

struct RangeBiasedPlacement : Placement {
    void forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, glm::ivec3 pos, const std::function<void(glm::ivec3)> &fn) override {
        const auto& cfg = std::get<TopSolidRangeConfig>(config);

        const int y = random.nextInt(random.nextInt(cfg.maximum - cfg.topOffset) + cfg.bottomOffset);

        fn(glm::ivec3(pos.x, y, pos.z));
    }
};