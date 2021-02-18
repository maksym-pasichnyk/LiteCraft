#pragma once

#include "src/world/gen/layer/traits/IAreaTransformer2.hpp"
#include "src/world/gen/layer/traits/IDimOffset0Transformer.hpp"
#include "src/world/gen/INoiseRandom.hpp"
#include "LayerUtil.hpp"
#include "src/world/gen/area/IArea.hpp"

#include <memory>

struct MixOceansLayer : IDimOffset0Transformer {
    int apply2(INoiseRandom& rand, const IArea auto& area1, const IArea auto& area2, int x, int z) {
        const int biomeInCenter1 = area1.getValue(getOffsetX(x), getOffsetZ(z));
        const int biomeInCenter2 = area2.getValue(getOffsetX(x), getOffsetZ(z));

        if (!LayerUtil::isOcean(biomeInCenter1)) {
            return biomeInCenter1;
        }

        const int radius = 8;
        const int step = 4;

        for (int xOffset = -radius; xOffset <= radius; xOffset += step) {
            for (int zOffset = -radius; zOffset <= radius; zOffset += step) {
                const int biome = area1.getValue(getOffsetX(x + xOffset), getOffsetZ(z + zOffset));

                if (!LayerUtil::isOcean(biome)) {
                    if (biomeInCenter2 == 44) {
                        return 45;
                    }

                    if (biomeInCenter2 == 10) {
                        return 46;
                    }
                }
            }
        }

        if (biomeInCenter1 == 24) {
            if (biomeInCenter2 == 45) {
                return 48;
            }

            if (biomeInCenter2 == 0) {
                return 24;
            }

            if (biomeInCenter2 == 46) {
                return 49;
            }

            if (biomeInCenter2 == 10) {
                return 50;
            }
        }

        return biomeInCenter2;
    }
};