#pragma once

#include "traits/IAreaTransformer0.hpp"

#include <memory>

struct IslandLayer {
    int get(INoiseRandom& rand, int x, int z) {
        if (x == 0 && z == 0) {
            return 1;
        }
        return rand.nextInt(10) == 0 ? 1 : 0;
    }
};