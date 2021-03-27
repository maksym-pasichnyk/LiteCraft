#pragma once

#include "Placement.hpp"

struct Spread32AbovePlacement : Placement {
    void forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, glm::ivec3 pos, const std::function<void(glm::ivec3)> &fn) override {
        const int y = random.nextInt(pos.y + 32);
        fn(glm::ivec3(pos.x, y, pos.z));
    }
};