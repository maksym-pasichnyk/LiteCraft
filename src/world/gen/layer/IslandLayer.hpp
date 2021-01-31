#pragma once

#include "src/world/gen/layer/traits/IAreaTransformer0.hpp"

#include <memory>

struct IslandLayer {
    int apply2(INoiseRandom& rand, int x, int z) {
        if (x == 0 && z == 0) {
            return 1;
        }
        return rand.random(10) == 0 ? 1 : 0;
    }
};