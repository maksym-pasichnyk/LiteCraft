#pragma once

#include "traits/ICastleTransformer.hpp"
#include "LayerUtil.hpp"

#include <set>
#include <memory>

struct ShoreLayer : ICastleTransformer<ShoreLayer> {
    inline static const std::set<int> shoreCompatible{26, 11, 12, 13, 140, 30, 31, 158, 10};
    inline static const std::set<int> jungleBiomes{168, 169, 21, 22, 23, 149, 151};

    int apply(INoiseRandom& rand, int north, int west, int south, int east, int center) {
        if (center == 14) {
            if (LayerUtil::isShallowOcean(north) || LayerUtil::isShallowOcean(west) || LayerUtil::isShallowOcean(south) || LayerUtil::isShallowOcean(east)) {
                return 15;
            }
        } else if (jungleBiomes.contains(center)) {
            if (!isJungleCompatible(north) || !isJungleCompatible(west) || !isJungleCompatible(south) || !isJungleCompatible(east)) {
                return 23;
            }

            if (LayerUtil::isOcean(north) || LayerUtil::isOcean(west) || LayerUtil::isOcean(south) || LayerUtil::isOcean(east)) {
                return 16;
            }
        } else if (center != 3 && center != 34 && center != 20) {
            if (shoreCompatible.contains(center)) {
                if (!LayerUtil::isOcean(center) && (LayerUtil::isOcean(north) || LayerUtil::isOcean(west) || LayerUtil::isOcean(south) || LayerUtil::isOcean(east))) {
                    return 26;
                }
            } else if (center != 37 && center != 38) {
                if (!LayerUtil::isOcean(center) && center != 7 && center != 6 && (LayerUtil::isOcean(north) || LayerUtil::isOcean(west) || LayerUtil::isOcean(south) || LayerUtil::isOcean(east))) {
                    return 16;
                }
            } else if (!LayerUtil::isOcean(north) && !LayerUtil::isOcean(west) && !LayerUtil::isOcean(south) && !LayerUtil::isOcean(east) && (!isMesa(north) || !isMesa(west) || !isMesa(south) || !isMesa(east))) {
                return 2;
            }
        } else if (!LayerUtil::isOcean(center) && (LayerUtil::isOcean(north) || LayerUtil::isOcean(west) || LayerUtil::isOcean(south) || LayerUtil::isOcean(east))) {
            return 25;
        }

        return center;
    }
    
    static /*constexpr*/ bool isJungleCompatible(int biome) {
        return jungleBiomes.contains(biome) || biome == 4 || biome == 5 || LayerUtil::isOcean(biome);
    }

    static constexpr bool isMesa(int biome) {
        return biome == 37 || biome == 38 || biome == 39 || biome == 165 || biome == 166 || biome == 167;
    }
};