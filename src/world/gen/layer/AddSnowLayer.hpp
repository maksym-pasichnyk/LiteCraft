#pragma once

#include "src/world/gen/layer/traits/IC1Transformer.hpp"
#include "src/world/gen/INoiseRandom.hpp"
#include "LayerUtil.hpp"

#include <memory>

struct AddSnowLayer : IC1Transformer<AddSnowLayer> {
    int apply(INoiseRandom& rand, int value) {
        if (LayerUtil::isShallowOcean(value)) {
            return value;
        }

        const int i = rand.random(6);
        if (i == 0) {
            return 4;
        }
        return i == 1 ? 3 : 1;
    }
};