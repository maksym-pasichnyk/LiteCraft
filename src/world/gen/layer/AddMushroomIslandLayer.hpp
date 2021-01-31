#pragma once

#include "src/world/gen/layer/traits/IBishopTransformer.hpp"
#include "LayerUtil.hpp"

#include <memory>

struct AddMushroomIslandLayer : IBishopTransformer<AddMushroomIslandLayer> {
    int apply(INoiseRandom& rand, int d0, int d1, int d2, int d3, int d4) {
        return LayerUtil::isShallowOcean(d4) &&
               LayerUtil::isShallowOcean(d3) &&
               LayerUtil::isShallowOcean(d0) &&
               LayerUtil::isShallowOcean(d2) &&
               LayerUtil::isShallowOcean(d1) &&
               rand.random(100) == 0 ? 14 : d4;
    }
};