#pragma once

#include "traits/IC1Transformer.hpp"
#include "../INoiseRandom.hpp"

#include <memory>

struct AddBambooForestLayer : IC1Transformer<AddBambooForestLayer> {
    int apply(INoiseRandom& rand, int value) {
        return rand.nextInt(10) == 0 && value == 21 ? 168 : value;
    }
};