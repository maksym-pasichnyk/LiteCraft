#pragma once

#include "traits/ICastleTransformer.hpp"

#include <memory>

struct RiverLayer : ICastleTransformer<RiverLayer> {
    int apply(INoiseRandom& rand, int north, int west, int south, int east, int center) {
        const int biome = riverFilter(center);

        return biome == riverFilter(east) &&
               biome == riverFilter(north) &&
               biome == riverFilter(west) &&
               biome == riverFilter(south) ? -1 : 7;
    }

private:
    static constexpr int riverFilter(int biome) {
        return biome >= 2 ? 2 + (biome & 1) : biome;
    }
};