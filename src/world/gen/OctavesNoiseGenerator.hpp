#pragma once

#include "INoiseGenerator.hpp"
#include "ImprovedNoiseGenerator.hpp"

#include "../../util/math/Math.hpp"

#include <optional>
#include <memory>
#include <vector>
#include <fmt/format.h>

struct OctavesNoiseGenerator : public INoiseGenerator {
    std::vector<std::optional<ImprovedNoiseGenerator>> octaves;
    std::vector<double> amplitudes;

    double field_227460_b_;
    double field_227461_c_;

    template <typename Random, typename IntStream>
    OctavesNoiseGenerator(Random&& rand, IntStream&& octaves)
        : OctavesNoiseGenerator(rand, createAmplitudes(std::forward<IntStream>(octaves))) {}

    OctavesNoiseGenerator(Random& rand, std::pair<int, std::vector<double>> in) : amplitudes(std::move(in.second)) {
        const int first = in.first;
        const int numAmplitudes = amplitudes.size();
        const int k = -first;

        octaves.resize(numAmplitudes);

        ImprovedNoiseGenerator improvedNoiseGenerator{rand};

        if (k >= 0 && k < numAmplitudes) {
            if (amplitudes[k] != 0.0) {
                octaves[k] = improvedNoiseGenerator;
            }
        }

        for (int i1 = k - 1; i1 >= 0; --i1) {
            if (i1 < numAmplitudes && amplitudes[i1] != 0.0) {
                octaves[i1] = ImprovedNoiseGenerator(rand);
            } else {
                rand.skip(262);
            }
        }

        if (k < numAmplitudes - 1) {
            auto j1 = static_cast<int64_t>(improvedNoiseGenerator.getNoiseValue(0.0, 0.0, 0.0, 0.0, 0.0) * 9.223372E18);
            auto sharedseedrandom = Random::from(j1);

            for (int l = k + 1; l < numAmplitudes; ++l) {
                if (l >= 0 && amplitudes[l] != 0.0) {
                    octaves[l] = ImprovedNoiseGenerator(sharedseedrandom);
                } else {
                    sharedseedrandom.skip(262);
                }
            }
        }


        field_227461_c_ = std::pow(2.0, -k);
        field_227460_b_ = std::pow(2.0, numAmplitudes - 1) / (std::pow(2.0, numAmplitudes) - 1.0);
    }

    template <typename IntStream>
    static auto createAmplitudes(IntStream&& octaves) -> std::pair<int, std::vector<double>> {
        const int first = -octaves.front();
        const int last = octaves.back();
        const int octavesCount = first + last + 1;

        std::vector<double> amplitudes(octavesCount);

        for (auto i : octaves) {
            amplitudes.at(i + first) = 1;
        }

        return {-first, std::move(amplitudes)};
    }

    double getValue(double x, double y, double z, double p_215462_7_, double p_215462_9_, bool useHeightOffset) const {
        double noise = 0.0;
        double d1 = field_227461_c_;
        double d2 = field_227460_b_;

        for (int i = 0; i < octaves.size(); ++i) {
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
        return getValue(x, y, z, 0.0, 0.0, false);
    }

    auto noiseAt(double x, double y, double z, double w) const -> double override {
        return getValue(x, y, 0.0, z, w, false);
    }

    ImprovedNoiseGenerator* getOctave(size_t i) {
        auto& octave = octaves[octaves.size() - i - 1];
        return octave.has_value() ? &*octave : nullptr;
    }

    inline static double maintainPrecision(double v) {
        return v - static_cast<double>(Math::lfloor(v / 3.3554432E7 + 0.5)) * 3.3554432E7;
    }
};