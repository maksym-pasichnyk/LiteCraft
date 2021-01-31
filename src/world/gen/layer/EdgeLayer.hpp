#pragma once

#include "src/world/gen/layer/traits/ICastleTransformer.hpp"
#include "src/world/gen/layer/traits/IC0Transformer.hpp"
#include "LayerUtil.hpp"

#include <memory>

struct EdgeLayer {
    struct CoolWarm : ICastleTransformer<CoolWarm> {
        int apply(INoiseRandom& rand, int north, int west, int south, int east, int center) {
            return center != 1 || north != 3 && west != 3 && east != 3 && south != 3 && north != 4 && west != 4 && east != 4 && south != 4 ? center : 2;
        }
    };

    struct HeatIce : ICastleTransformer<HeatIce> {
        int apply(INoiseRandom& rand, int north, int west, int south, int east, int center) {
            return center != 4 || north != 1 && west != 1 && east != 1 && south != 1 && north != 2 && west != 2 && east != 2 && south != 2 ? center : 3;
        }
    };

    struct Special : IC0Transformer<Special> {
        int apply(INoiseRandom& rand, int value) {
            if (!LayerUtil::isShallowOcean(value) && rand.random(13) == 0) {
                value |= (1 + rand.random(15)) << 8 & 3840;
            }
            return value;
        }
    };
};