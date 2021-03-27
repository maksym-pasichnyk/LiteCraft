#pragma once

#include "Placement.hpp"

struct IcebergPlacement : Placement {
    void forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, glm::ivec3 pos, const std::function<void(glm::ivec3)> &fn) override {
        const int x = random.nextInt(8) + 4 + pos.x;
        const int y = random.nextInt(8) + 4 + pos.z;
        fn(glm::ivec3(x, pos.y, y));
    }
};