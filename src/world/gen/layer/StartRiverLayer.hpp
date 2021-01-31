#pragma once

#include "src/world/gen/layer/traits/IC0Transformer.hpp"
#include "LayerUtil.hpp"

#include <memory>

struct StartRiverLayer : IC0Transformer<StartRiverLayer> {
    int apply(INoiseRandom& rand, int value) {
        return LayerUtil::isShallowOcean(value) ? value : rand.random(299999) + 2;
    }
};