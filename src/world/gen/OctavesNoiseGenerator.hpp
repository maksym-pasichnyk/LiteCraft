#pragma once

#include "INoiseGenerator.hpp"
#include "ImprovedNoiseGenerator.hpp"

#include <memory>

namespace Math {
    inline static long lfloor(double value) {
        long i = (long) value;
        return value < (double) i ? i - 1L : i;
    }

    inline static float lerp(float pct, float start, float end) {
        return start + pct * (end - start);
    }

    inline static double lerp(double pct, double start, double end) {
        return start + pct * (end - start);
    }

    inline static double clamp(double num, double min, double max) {
        return num < min ? min : num > max ? max : num;
    }

    inline static double clampedLerp(double lowerBnd, double upperBnd, double slide) {
        return slide < 0.0 ? lowerBnd : slide > 1.0 ? upperBnd : lerp(slide, lowerBnd, upperBnd);
    }
}

struct OctavesNoiseGenerator : public INoiseGenerator {
    std::vector<std::optional<ImprovedNoiseGenerator>> octaves;
    std::vector<double> amplitudes;

    double field_227460_b_;
    double field_227461_c_;

    template <typename Random, typename IntStream>
    OctavesNoiseGenerator(Random&& rand, IntStream&& ints)
        : OctavesNoiseGenerator(rand, createOctaves(std::forward<IntStream>(ints))) {}

    OctavesNoiseGenerator(Random& rand, std::pair<int, std::vector<double>> in) : amplitudes(std::move(in.second)) {
        const int first = in.first;
        const int j = amplitudes.size();
        const int k = -first;

        octaves.resize(j);

        ImprovedNoiseGenerator improvedNoiseGenerator{rand};

        if (k >= 0 && k < j) {
            if (amplitudes[k] != 0.0) {
                octaves[k] = improvedNoiseGenerator;
            }
        }

        for (int i1 = k - 1; i1 >= 0; --i1) {
            if (i1 < j && amplitudes[i1] != 0.0) {
                octaves[i1] = ImprovedNoiseGenerator(rand);
            } else {
                rand.skip(262);
            }
        }

        if (k < j - 1) {
            auto j1 = static_cast<int64_t>(improvedNoiseGenerator.getNoiseValue(0.0, 0.0, 0.0, 0.0, 0.0) * 9.223372E18);
            auto sharedseedrandom = Random::from(j1);

            for (int l = k + 1; l < j; ++l) {
                if (l >= 0 && amplitudes[l] != 0.0) {
                    octaves[l] = ImprovedNoiseGenerator(sharedseedrandom);
                } else {
                    sharedseedrandom.skip(262);
                }
            }
        }


        field_227461_c_ = std::pow(2.0, -k);
        field_227460_b_ = std::pow(2.0, j - 1) / (std::pow(2.0, j) - 1.0);
    }

    template <typename IntStream>
    static auto createOctaves(IntStream&& ints) -> std::pair<int, std::vector<double>> {
        const int first = -*ints.begin();
        const int last = *ints.end();
        const int octavesCount = first + last + 1;

        std::vector<double> doubles(octavesCount);

        for (auto i : ints) {
            doubles.at(i + first) = 1;
        }

        return {-first, std::move(doubles)};
    }

    double getValue(double x, double y, double z, double p_215462_7_, double p_215462_9_, bool useHeightOffset) const {
        double noise = 0.0;
        double d1 = field_227461_c_;
        double d2 = field_227460_b_;

        for(int i = 0; i < octaves.size(); ++i) {
            auto& octave = octaves[i];
            if (octave.has_value()) {
                noise += amplitudes[i] * octave->getNoiseValue(
                        maintainPrecision(x * d1),
                        useHeightOffset ? -octave->yCoord : maintainPrecision(y * d1),
                        maintainPrecision(z * d1),
                        p_215462_7_ * d1,
                        p_215462_9_ * d1) * d2;
            }

            d1 *= 2.0;
            d2 /= 2.0;
        }

        return noise;
    }

    auto noiseAt(double x, double y, double z) const -> double {
        return getValue(x, y, 0.0, z, 0.0, false);
    }

    auto noiseAt(double x, double y, double z, double w) const -> double override {
        return getValue(x, y, 0.0, z, w, false);
    }

    ImprovedNoiseGenerator* getOctave(size_t i) {
        auto& octave = octaves[octaves.size() - i - 1];
        return octave.has_value() ? &*octave : nullptr;
    }

    inline static double maintainPrecision(double v) {
        return v - (double) Math::lfloor(v / 3.3554432E7 + 0.5) * 3.3554432E7;
    }
};