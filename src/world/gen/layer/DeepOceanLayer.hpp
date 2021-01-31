#pragma once

#include "src/world/gen/layer/traits/ICastleTransformer.hpp"
#include "src/world/gen/INoiseRandom.hpp"
#include "LayerUtil.hpp"

#include <memory>

struct DeepOceanLayer : ICastleTransformer<DeepOceanLayer> {
    int apply(INoiseRandom& rand, int north, int west, int south, int east, int center) {
        if (LayerUtil::isShallowOcean(center)) {
            int sameNeighbours = 0;
            if (LayerUtil::isShallowOcean(north)) {
                ++sameNeighbours;
            }

            if (LayerUtil::isShallowOcean(west)) {
                ++sameNeighbours;
            }

            if (LayerUtil::isShallowOcean(east)) {
                ++sameNeighbours;
            }

            if (LayerUtil::isShallowOcean(south)) {
                ++sameNeighbours;
            }

            if (sameNeighbours > 3) {
                if (center == 44) {
                    return 47;
                }

                if (center == 45) {
                    return 48;
                }

                if (center == 0) {
                    return 24;
                }

                if (center == 46) {
                    return 49;
                }

                if (center == 10) {
                    return 50;
                }

                return 24;
            }
        }

        return center;
    }
};