#pragma once

#include "SimplexNoiseGenerator.hpp"

#include <vector>
#include <tl/optional.hpp>
#include <algorithm>
#include <spdlog/spdlog.h>
#include <range/v3/algorithm.hpp>

struct PerlinNoiseGenerator : public INoiseGenerator {
    std::vector<tl::optional<SimplexNoiseGenerator>> noiseLevels;
    double field_227460_b_;
    double field_227461_c_;

    template <typename IntStream>
    PerlinNoiseGenerator(Random&& rand, IntStream&& octaves)
        : PerlinNoiseGenerator(rand, std::forward<IntStream>(octaves)) {}

    template <typename IntStream>
    PerlinNoiseGenerator(Random& rand, IntStream&& octaves) {
        const int first = -octaves.front();
        const int last = octaves.back();

        const int octavesCount = first + last + 1;
        SimplexNoiseGenerator simplexNoiseGenerator{rand};

        noiseLevels.resize(octavesCount);
        if (last >= 0 && last < octavesCount && ranges::contains(octaves, 0)) {
            noiseLevels[last] = simplexNoiseGenerator;
        }

        for(int i1 = last + 1; i1 < octavesCount; ++i1) {
            if (i1 >= 0 && ranges::contains(octaves, last - i1)) {
                noiseLevels[i1] = SimplexNoiseGenerator(rand);
            } else {
                rand.skip(262);
            }
        }

        if (last > 0) {
            auto k1 = static_cast<int64_t>(simplexNoiseGenerator.getValue3D(simplexNoiseGenerator.xo, simplexNoiseGenerator.yo, simplexNoiseGenerator.zo) * 9.223372E18);
            auto sharedseedrandom = Random::from(k1);

            for (int j1 = last - 1; j1 >= 0; --j1) {
                if (j1 < octavesCount && ranges::contains(octaves, last - j1)) {
                    noiseLevels[j1] = SimplexNoiseGenerator(sharedseedrandom);
                } else {
                    sharedseedrandom.skip(262);
                }
            }
        }

        field_227461_c_ = std::pow(2.0, last);
        field_227460_b_ = 1.0 / (std::pow(2.0, octavesCount) - 1.0);
    }

    auto noiseAt(double x, double y, bool useOffsets) const -> double {
        double d0 = 0.0;
        double d1 = field_227461_c_;
        double d2 = field_227460_b_;

        for (auto& noiseLevel : noiseLevels) {
            if (noiseLevel.has_value()) {
                d0 += d2 * noiseLevel->getValue2D(
                        x * d1 + (useOffsets ? noiseLevel->xo : 0),
                        y * d1 + (useOffsets ? noiseLevel->yo : 0)
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
