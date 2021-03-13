#pragma once

#include "OctavesNoiseGenerator.hpp"

#include <memory>

struct MaxMinNoiseMixer {
    std::unique_ptr<OctavesNoiseGenerator> noise1;
    std::unique_ptr<OctavesNoiseGenerator> noise2;
    double field_237208_a_;

    MaxMinNoiseMixer(Random&& rand, int octaves, const std::vector<double>& amplitudes)
        : MaxMinNoiseMixer(rand, octaves, amplitudes) {}

    MaxMinNoiseMixer(Random& rand, int octaves, const std::vector<double>& amplitudes) {
        noise1 = std::make_unique<OctavesNoiseGenerator>(rand, std::pair{octaves, amplitudes});
        noise2 = std::make_unique<OctavesNoiseGenerator>(rand, std::pair{octaves, amplitudes});

        int i = std::numeric_limits<int>::max();
        int j = std::numeric_limits<int>::min();

        for (size_t k = 0; k < amplitudes.size(); k++) {
            if (amplitudes[k] != 0.0) {
                i = std::min(i, static_cast<int>(k));
                j = std::max(j, static_cast<int>(k));
            }
        }

        field_237208_a_ = 0.16666666666666666 / func_237212_a_(j - i);
    }

    double noiseAt(double x, double y, double z) const {
        double d0 = x * 1.0181268882175227;
        double d1 = y * 1.0181268882175227;
        double d2 = z * 1.0181268882175227;
        return (noise1->noiseAt(x, y, z) + noise2->noiseAt(d0, d1, d2)) * field_237208_a_;
    }

    static double func_237212_a_(int v) {
        return 0.1 * (1.0 + 1.0 / static_cast<double>(v + 1));
    }
};