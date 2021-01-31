#pragma once

#include "src/world/gen/layer/traits/IC1Transformer.hpp"
#include "src/world/gen/INoiseRandom.hpp"

struct RareBiomeLayer : IC1Transformer<RareBiomeLayer> {
    int apply(INoiseRandom& rand, int value) {
        return rand.random(57) == 0 && value == 1 ? 129 : value;
    }
};