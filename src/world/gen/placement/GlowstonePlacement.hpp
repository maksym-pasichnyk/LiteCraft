#pragma once

#include "Placement.hpp"

struct GlowstonePlacement : Placement {
    void forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, glm::ivec3 pos, const std::function<void(glm::ivec3)> &fn) override {
        const auto& cfg = std::get<FeatureSpreadConfig>(config);
        const int count = random.nextInt(random.nextInt(cfg.spread.getCount(random)) + 1);
        for (int i = 0; i < count; i++) {
            const int x = random.nextInt(16) + pos.x;
            const int z = random.nextInt(16) + pos.z;
            const int y = random.nextInt(120) + 4;
            fn(glm::ivec3(x, y, z));
        }
    }
};