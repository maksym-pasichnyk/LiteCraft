#pragma once

#include "Placement.hpp"

struct SquarePlacement : Placement {
    void forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, glm::ivec3 pos, const std::function<void(glm::ivec3)> &fn) override {
        const int x = random.nextInt(16) + pos.x;
        const int z = random.nextInt(16) + pos.z;
        fn(glm::ivec3(x, pos.y, z));
    }
};