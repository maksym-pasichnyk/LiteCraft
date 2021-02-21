#pragma once

#include "traits/ICastleTransformer.hpp"
#include "LayerUtil.hpp"

#include <memory>

struct EdgeBiomeLayer : ICastleTransformer<EdgeBiomeLayer> {
    int apply(INoiseRandom& rand, int north, int west, int south, int east, int center) {
        int biome = 0;
        if (!matchExtremeHills(biome, center)) {
            if (!replaceBiomeEdge(biome, north, west, south, east, center, 38, 37) &&
                !replaceBiomeEdge(biome, north, west, south, east, center, 39, 37) &&
                !replaceBiomeEdge(biome, north, west, south, east, center, 32, 5)) {

                if (center != 2 || north != 12 && west != 12 && east != 12 && south != 12) {
                    if (center == 6) {
                        if (north == 2 || west == 2 || east == 2 || south == 2 || north == 30 || west == 30 ||
                            east == 30 ||
                            south == 30 || north == 12 || west == 12 || east == 12 || south == 12) {
                            return 1;
                        }

                        if (north == 21 || south == 21 || west == 21 || east == 21 || north == 168 || south == 168 ||
                            west == 168 || east == 168) {
                            return 23;
                        }
                    }

                    return center;
                }
                return 34;
            }
        }
        return biome;
    }

private:
    static bool matchExtremeHills(int &out, int biome) {
        if (!LayerUtil::areBiomesSimilar(biome, 3)) {
            return false;
        }
        out = biome;
        return true;
    }

    static bool replaceBiomeEdge(int &out, int north, int west, int south, int east, int center, int extectedBiome, int defaultBiome) {
        if (center != extectedBiome) {
            return false;
        }
        if (LayerUtil::areBiomesSimilar(north, extectedBiome) && LayerUtil::areBiomesSimilar(west, extectedBiome) && LayerUtil::areBiomesSimilar(east, extectedBiome) && LayerUtil::areBiomesSimilar(south, extectedBiome)) {
            out = center;
        } else {
            out = defaultBiome;
        }
        return true;
    }
};