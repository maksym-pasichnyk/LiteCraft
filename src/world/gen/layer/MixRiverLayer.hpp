#pragma once

#include "traits/IAreaTransformer2.hpp"
#include "traits/IDimOffset0Transformer.hpp"
#include "LayerUtil.hpp"

struct MixRiverLayer : IDimOffset0Transformer {
    int get(INoiseRandom& rand, const IArea auto& area1, const IArea auto& area2, int x, int z) {
        const int biomeInCenter1 = area1.getValue(getOffsetX(x), getOffsetZ(z));
        const int biomeInCenter2 = area2.getValue(getOffsetX(x), getOffsetZ(z));

        if (LayerUtil::isOcean(biomeInCenter1)) {
            return biomeInCenter1;
        }

        if (biomeInCenter2 == 7) {
            if (biomeInCenter1 == 12) {
                return 11;
            }
            return biomeInCenter1 != 14 && biomeInCenter1 != 15 ? biomeInCenter2 & 255 : 15;
        }
        return biomeInCenter1;
    }
};