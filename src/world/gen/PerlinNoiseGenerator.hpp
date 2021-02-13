#pragma once

#include "SimplexNoiseGenerator.hpp"

#include <optional>
#include <vector>

struct PerlinNoiseGenerator : public INoiseGenerator {
    std::vector<std::optional<SimplexNoiseGenerator>> noiseLevels;
    double field_227460_b_;
    double field_227461_c_;

    PerlinNoiseGenerator(Random&& rand, int min, int max) : PerlinNoiseGenerator(rand, min, max) {}
    PerlinNoiseGenerator(Random& rand, int min, int max) {
        const int i = -min;
        const int j = max;
        const int octavesCount = i + j + 1;
        {
            SimplexNoiseGenerator simplexNoiseGenerator{rand};

            noiseLevels.resize(octavesCount);
            if (j >= 0 && j < octavesCount && (min <= 0 && 0 <= max)) {
                noiseLevels[j] = simplexNoiseGenerator;
            }

            for(int i1 = j + 1; i1 < octavesCount; ++i1) {
                if (i1 >= 0 && (min <= (j - i1) && (j - i1) <= max)) {
                    noiseLevels[i1] = SimplexNoiseGenerator(rand);
                } else {
                    rand.skip(262);
                }
            }

            if (j > 0) {
                auto k1 = static_cast<int64_t>(simplexNoiseGenerator.getValue3D(simplexNoiseGenerator.xo, simplexNoiseGenerator.yo, simplexNoiseGenerator.zo) * 9.223372E18);
                auto sharedseedrandom = Random::from(k1);

                for (int j1 = j - 1; j1 >= 0; --j1) {
                    if (j1 < octavesCount && (min <= (j - j1) && (j - j1) <= max)) {
                        noiseLevels[j1] = SimplexNoiseGenerator(sharedseedrandom);
                    } else {
                        sharedseedrandom.skip(262);
                    }
                }
            }

            field_227461_c_ = std::pow(2.0, j);
            field_227460_b_ = 1.0 / (std::pow(2.0, octavesCount) - 1.0);
        }
    }

    auto noiseAt(double x, double y, bool useOffsets) const -> double {
        double d0 = 0.0;
        double d1 = field_227461_c_;
        double d2 = field_227460_b_;

        for (auto& simplexnoisegenerator : noiseLevels) {
            if (simplexnoisegenerator.has_value()) {
                d0 += d2 * simplexnoisegenerator->getValue2D(
                        x * d1 + (useOffsets ? simplexnoisegenerator->xo : 0),
                        y * d1 + (useOffsets ? simplexnoisegenerator->yo : 0)
                );
            }

            d1 /= 2.0;
            d2 *= 2.0;
        }
        return d0;
    }

    auto noiseAt(double x, double y, double z, double w) const -> double override {
        return noiseAt(x, y, true) * 0.55;
    }
};