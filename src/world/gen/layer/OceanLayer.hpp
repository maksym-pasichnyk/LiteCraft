#pragma once

#include "traits/IAreaTransformer0.hpp"
#include "../ImprovedNoiseGenerator.hpp"
#include "../INoiseRandom.hpp"

#include <memory>

struct OceanLayer {
    int apply2(INoiseRandom& rand, int x, int z) {
        const double noise = rand.getNoiseGenerator().getNoiseValue((double) x / 8.0, (double) z / 8.0, 0.0, 0.0, 0.0);

        if (noise > 0.4) {
            return 44;
        }
        if (noise > 0.2) {
            return 45;
        }
        if (noise < -0.4) {
            return 10;
        }
        return noise < -0.2 ? 46 : 0;
    }
};