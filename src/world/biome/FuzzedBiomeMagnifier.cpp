#include "FuzzedBiomeMagnifier.hpp"
#include "BiomeReader.hpp"
#include "../../util/FastRandom.hpp"

#include <array>

namespace {
    double square(double x) {
        return x * x;
    }

    int64_t floorMod(int64_t x, int64_t y) {
//        return x - floorDiv(x, y) * y;
        return ((x % y) + y) % y;
    }

    double randomDouble(int64_t seed) {
        return (static_cast<double>(floorMod(seed >> 24, 1024L)) / 1024.0 - 0.5) * 0.9;
    }

    double distanceToCorner(int64_t seed, int x, int y, int z, double scaleX, double scaleY, double scaleZ) {
        int64_t i0 = FastRandom::mix(seed, x);
        i0 = FastRandom::mix(i0, y);
        i0 = FastRandom::mix(i0, z);
        i0 = FastRandom::mix(i0, x);
        i0 = FastRandom::mix(i0, y);
        i0 = FastRandom::mix(i0, z);
        const double d0 = randomDouble(i0);
        i0 = FastRandom::mix(i0, seed);
        const double d1 = randomDouble(i0);
        i0 = FastRandom::mix(i0, seed);
        const double d2 = randomDouble(i0);
        return square(scaleZ + d2) + square(scaleY + d1) + square(scaleX + d0);
    }
}

Biome *FuzzedBiomeMagnifier::getBiome(int64_t seed, int x, int y, int z, BiomeReader &biomeReader) {
    const int i = x - 2;
    const int j = y - 2;
    const int k = z - 2;
    const int l = i >> 2;
    const int i1 = j >> 2;
    const int j1 = k >> 2;
    const double d0 = static_cast<double>(i & 3) / 4.0;
    const double d1 = static_cast<double>(j & 3) / 4.0;
    const double d2 = static_cast<double>(k & 3) / 4.0;
    std::array<double, 8> doubles{};

    for (int k1 = 0; k1 < 8; ++k1) {
        const bool flag = (k1 & 4) == 0;
        const bool flag1 = (k1 & 2) == 0;
        const bool flag2 = (k1 & 1) == 0;
        const int l1 = flag ? l : l + 1;
        const int i2 = flag1 ? i1 : i1 + 1;
        const int j2 = flag2 ? j1 : j1 + 1;
        const double d3 = flag ? d0 : d0 - 1.0;
        const double d4 = flag1 ? d1 : d1 - 1.0;
        const double d5 = flag2 ? d2 : d2 - 1.0;
        doubles[k1] = distanceToCorner(seed, l1, i2, j2, d3, d4, d5);
    }

    int k2 = 0;
    double d6 = doubles[0];

    for (int l2 = 1; l2 < 8; ++l2) {
        if (d6 > doubles[l2]) {
            k2 = l2;
            d6 = doubles[l2];
        }
    }

    const int i3 = (k2 & 4) == 0 ? l : l + 1;
    const int j3 = (k2 & 2) == 0 ? i1 : i1 + 1;
    const int k3 = (k2 & 1) == 0 ? j1 : j1 + 1;
    return biomeReader.getNoiseBiome(i3, j3, k3);
}
