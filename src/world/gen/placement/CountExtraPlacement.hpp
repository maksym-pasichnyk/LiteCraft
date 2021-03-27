#pragma once

#include "Placement.hpp"

struct CountExtraPlacement : Placement {
    void forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, glm::ivec3 pos, const std::function<void(glm::ivec3)> &fn) override {
        const auto& cfg = std::get<AtSurfaceWithExtraConfig>(config);
        const int count = cfg.count + (random.nextFloat() < cfg.extraChance ? cfg.extraCount : 0);
        for (int i = 0; i < count; i++) {
            fn(pos);
        }
    }
};