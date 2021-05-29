#pragma once

#include "traits/IC1Transformer.hpp"
#include "../INoiseRandom.hpp"

struct RareBiomeLayer : IC1Transformer<RareBiomeLayer> {
    int apply(INoiseRandom& rand, int value) {
        return rand.nextInt(57) == 0 && value == 1 ? 129 : value;
    }
};