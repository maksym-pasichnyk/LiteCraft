#pragma once

#include "traits/IAreaTransformer1.hpp"
#include "../IExtendedNoiseRandom.hpp"
#include "../area/IArea.hpp"

#include <memory>

template <typename T>
struct ZoomLayer {
    int getOffsetX(int x) {
        return x >> 1;
    }

    int getOffsetZ(int z) {
        return z >> 1;
    }

    int apply2(IExtendedNoiseRandom& context, const IArea auto& area, int x, int z) {
        const int biome1 = area.getValue(getOffsetX(x), getOffsetZ(z));
        context.setPosition(x >> 1 << 1, z >> 1 << 1);
        const int j = x & 1;
        const int k = z & 1;
        if (j == 0 && k == 0) {
            return biome1;
        }
        const int biome2 = area.getValue(getOffsetX(x), getOffsetZ(z + 1));
        const int randomBiome1 = context.pickRandom(biome1, biome2);
        if (j == 0 && k == 1) {
            return randomBiome1;
        }
        const int biome3 = area.getValue(getOffsetX(x + 1), getOffsetZ(z));
        const int randomBiome2 = context.pickRandom(biome1, biome3);
        if (j == 1 && k == 0) {
            return randomBiome2;
        }
        const int biome4 = area.getValue(getOffsetX(x + 1), getOffsetZ(z + 1));
        return static_cast<T*>(this)->pickZoomed(context, biome1, biome3, biome2, biome4);
    }
};

struct ZoomLayerNormal : ZoomLayer<ZoomLayerNormal> {
    int pickZoomed(IExtendedNoiseRandom& rand, int first, int second, int third, int fourth) {
        if (second == third && third == fourth) {
            return second;
        }
        if (first == second && first == third) {
            return first;
        }
        if (first == second && first == fourth) {
            return first;
        }
        if (first == third && first == fourth) {
            return first;
        }
        if (first == second && third != fourth) {
            return first;
        }
        if (first == third && second != fourth) {
            return first;
        }
        if (first == fourth && second != third) {
            return first;
        }
        if (second == third && first != fourth) {
            return second;
        }
        if (second == fourth && first != third) {
            return second;
        }
        return third == fourth && first != second ? third : rand.pickRandom(first, second, third, fourth);
    }
};

struct ZoomLayerFuzzy : ZoomLayer<ZoomLayerFuzzy> {
    int pickZoomed(IExtendedNoiseRandom& rand, int first, int second, int third, int fourth) {
        return rand.pickRandom(first, second, third, fourth);
    }
};