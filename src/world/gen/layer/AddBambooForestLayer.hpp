#pragma once

#include "src/world/gen/layer/traits/IC1Transformer.hpp"
#include "src/world/gen/INoiseRandom.hpp"

#include <memory>

struct AddBambooForestLayer : IC1Transformer<AddBambooForestLayer> {
    int apply(INoiseRandom& rand, int value) {
        return rand.random(10) == 0 && value == 21 ? 168 : value;
    }
};