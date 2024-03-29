#pragma once

#include "traits/ICastleTransformer.hpp"
#include "LayerUtil.hpp"

#include <memory>

struct RemoveTooMuchOceanLayer : ICastleTransformer<RemoveTooMuchOceanLayer> {
    int apply(INoiseRandom& rand, int north, int west, int south, int east, int center) {
        return LayerUtil::isShallowOcean(center) &&
               LayerUtil::isShallowOcean(north) &&
               LayerUtil::isShallowOcean(west) &&
               LayerUtil::isShallowOcean(east) &&
               LayerUtil::isShallowOcean(south) &&
               rand.nextInt(2) == 0 ? 1 : center;
    }
};