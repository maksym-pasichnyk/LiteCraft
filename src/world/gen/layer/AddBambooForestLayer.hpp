#pragma once

#include "traits/IC1Transformer.hpp"
#include "../INoiseRandom.hpp"

#include <memory>

struct AddBambooForestLayer : IC1Transformer<AddBambooForestLayer> {
    int apply(INoiseRandom& rand, int value) {
        return rand.random(10) == 0 && value == 21 ? 168 : value;
    }
};