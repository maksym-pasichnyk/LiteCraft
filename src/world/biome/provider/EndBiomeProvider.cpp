#include "EndBiomeProvider.hpp"

#include <cmath>
#include <algorithm>

EndBiomeProvider::EndBiomeProvider(int64_t seed, Biome *theEndBiome, Biome *endHighlandsBiome, Biome *endMidlandsBiome, Biome *smallEndIslandsBiome, Biome *endBarrensBiome)
    : theEndBiome{theEndBiome}
    , endHighlandsBiome{endHighlandsBiome}
    , endMidlandsBiome{endMidlandsBiome}
    , smallEndIslandsBiome{smallEndIslandsBiome}
    , endBarrensBiome{endBarrensBiome} {
    auto rand = Random::from(seed);
    rand.skip(17292);
    generator = std::make_unique<SimplexNoiseGenerator>(rand);
}

Biome *EndBiomeProvider::getNoiseBiome(int x, int y, int z) {
    const int i = x >> 2;
    const int j = z >> 2;
    if (static_cast<int64_t>(i) * static_cast<int64_t>(i) + static_cast<int64_t>(j) * static_cast<int64_t>(j) <= 4096L) {
        return theEndBiome;
    }
    const float f = getRandomNoise(i * 2 + 1, j * 2 + 1);
    if (f > 40.0F) {
        return endHighlandsBiome;
    }
    if (f >= 0.0F) {
        return endMidlandsBiome;
    }
    return f < -20.0F ? smallEndIslandsBiome : endBarrensBiome;
}

float EndBiomeProvider::getRandomNoise(int x, int z) {
    const int i = x / 2;
    const int j = z / 2;
    const int k = x % 2;
    const int l = z % 2;

    float f = std::clamp(100.0F - std::sqrt(static_cast<float>(x * x + z * z)) * 8.0F, -100.0F, 80.0F);

    for (int i1 = -12; i1 <= 12; ++i1) {
        for (int j1 = -12; j1 <= 12; ++j1) {
            const auto k1 = static_cast<int64_t>(i) + i1;
            const auto l1 = static_cast<int64_t>(j) + j1;

            if (k1 * k1 + l1 * l1 > 4096L) {
                if (generator->getValue2D(static_cast<double>(k1), static_cast<double>(l1)) < -0.9) {
                    const auto f0 = std::abs(static_cast<float>(k1)) * 3439.0F +
                                    std::abs(static_cast<float>(l1)) * 147.0F;
                    const auto f1 = std::fmod(f0, 13.0F) + 9.0F;
                    const auto f2 = static_cast<float>(k - i1 * 2);
                    const auto f3 = static_cast<float>(l - j1 * 2);
                    const auto f4 = 100.0F - std::sqrt(f2 * f2 + f3 * f3) * f1;
                    f = std::max(f, std::clamp(f4, -100.0F, 80.0F));
                }
            }
        }
    }

    return f;
}
