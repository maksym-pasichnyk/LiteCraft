#pragma once

#include "traits/ICastleTransformer.hpp"

#include <memory>

struct SmoothLayer : ICastleTransformer<SmoothLayer> {
    int apply(INoiseRandom& rand, int north, int west, int south, int east, int center) {
        const bool westEqualsEast = west == east;
        const bool northEqualsSouth = north == south;

        if (westEqualsEast == northEqualsSouth) {
            if (westEqualsEast) {
                return rand.nextInt(2) == 0 ? east : north;
            }
            return center;
        }

        return westEqualsEast ? east : north;
    }
};