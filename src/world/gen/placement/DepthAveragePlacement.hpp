#pragma once

#include "Placement.hpp"

struct DepthAveragePlacement : Placement {
    void forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, glm::ivec3 pos, const std::function<void(glm::ivec3)> &fn) override {
        const auto& cfg = std::get<DepthAverageConfig>(config);
        const int y = random.nextInt(cfg.spread) + random.nextInt(cfg.spread) - cfg.spread + cfg.baseline;
        fn(glm::ivec3(pos.x, y, pos.z));
    }
};