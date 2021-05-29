#pragma once

#include "traits/IAreaTransformer2.hpp"
#include "traits/IDimOffset1Transformer.hpp"
#include "LayerUtil.hpp"

#include <memory>

struct HillsLayer : IDimOffset1Transformer {
    int get(INoiseRandom& rand, const IArea auto& area1, const IArea auto& area2, int x, int z) {
        const int biomeInCenter1 = area1.getValue(getOffsetX(x + 1), getOffsetZ(z + 1));
        const int biomeInCenter2 = area2.getValue(getOffsetX(x + 1), getOffsetZ(z + 1));

        if (biomeInCenter1 > 255) {
//            LOGGER.debug("old! {}", biomeInCenter1);
        }

        const int k = (biomeInCenter2 - 2) % 29;
        if (!LayerUtil::isShallowOcean(biomeInCenter1) && biomeInCenter2 >= 2 && k == 1) {
            return getHillBiome(biomeInCenter1, biomeInCenter1);
        }
        if (rand.nextInt(3) == 0 || k == 0) {
            int referenceBiome = biomeInCenter1;
            if (biomeInCenter1 == 2) {
                referenceBiome = 17;
            } else if (biomeInCenter1 == 4) {
                referenceBiome = 18;
            } else if (biomeInCenter1 == 27) {
                referenceBiome = 28;
            } else if (biomeInCenter1 == 29) {
                referenceBiome = 1;
            } else if (biomeInCenter1 == 5) {
                referenceBiome = 19;
            } else if (biomeInCenter1 == 32) {
                referenceBiome = 33;
            } else if (biomeInCenter1 == 30) {
                referenceBiome = 31;
            } else if (biomeInCenter1 == 1) {
                referenceBiome = rand.nextInt(3) == 0 ? 18 : 4;
            } else if (biomeInCenter1 == 12) {
                referenceBiome = 13;
            } else if (biomeInCenter1 == 21) {
                referenceBiome = 22;
            } else if (biomeInCenter1 == 168) {
                referenceBiome = 169;
            } else if (biomeInCenter1 == 0) {
                referenceBiome = 24;
            } else if (biomeInCenter1 == 45) {
                referenceBiome = 48;
            } else if (biomeInCenter1 == 46) {
                referenceBiome = 49;
            } else if (biomeInCenter1 == 10) {
                referenceBiome = 50;
            } else if (biomeInCenter1 == 3) {
                referenceBiome = 34;
            } else if (biomeInCenter1 == 35) {
                referenceBiome = 36;
            } else if (LayerUtil::areBiomesSimilar(biomeInCenter1, 38)) {
                referenceBiome = 37;
            } else if ((biomeInCenter1 == 24 || biomeInCenter1 == 48 || biomeInCenter1 == 49 || biomeInCenter1 == 50) &&
                    rand.nextInt(3) == 0) {
                referenceBiome = rand.nextInt(2) == 0 ? 1 : 4;
            }

            if (k == 0 && referenceBiome != biomeInCenter1) {
                referenceBiome = getHillBiome(referenceBiome, biomeInCenter1);
            }

            if (referenceBiome != biomeInCenter1) {
                int sameNeighbours = 0;
                if (LayerUtil::areBiomesSimilar(area1.getValue(getOffsetX(x + 1), getOffsetZ(z + 0)), biomeInCenter1)) {
                    ++sameNeighbours;
                }

                if (LayerUtil::areBiomesSimilar(area1.getValue(getOffsetX(x + 2), getOffsetZ(z + 1)), biomeInCenter1)) {
                    ++sameNeighbours;
                }

                if (LayerUtil::areBiomesSimilar(area1.getValue(getOffsetX(x + 0), getOffsetZ(z + 1)), biomeInCenter1)) {
                    ++sameNeighbours;
                }

                if (LayerUtil::areBiomesSimilar(area1.getValue(getOffsetX(x + 1), getOffsetZ(z + 2)), biomeInCenter1)) {
                    ++sameNeighbours;
                }

                if (sameNeighbours >= 3) {
                    return referenceBiome;
                }
            }
        }

        return biomeInCenter1;
    }

private:
    static int getHillBiome(int biome, int defaultBiome) {
        switch (biome) {
            case 1: return 129;
            case 2: return 130;
            case 3: return 131;
            case 4: return 132;
            case 5: return 133;
            case 6: return 134;
            case 12: return 140;
            case 21: return 149;
            case 23: return 151;
            case 27: return 155;
            case 28: return 156;
            case 29: return 157;
            case 30: return 158;
            case 32: return 160;
            case 33: return 161;
            case 34: return 162;
            case 35: return 163;
            case 36: return 164;
            case 37: return 165;
            case 38: return 166;
            case 39: return 167;
            default: return defaultBiome;
        }
    }
};