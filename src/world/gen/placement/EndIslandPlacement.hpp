#pragma once

#include "Placement.hpp"

struct EndIslandPlacement : Placement {
    void forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, glm::ivec3 pos, const std::function<void(glm::ivec3)> &fn) override {
        if (random.nextInt(14) == 0) {
            fn(pos + glm::ivec3(random.nextInt(16), 55 + random.nextInt(16), random.nextInt(16)));
            if (random.nextInt(4) == 0) {
                fn(pos + glm::ivec3(random.nextInt(16), 55 + random.nextInt(16), random.nextInt(16)));
            }
        }
    }
};