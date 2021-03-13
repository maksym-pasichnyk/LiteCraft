#pragma once

#include "BiomeProvider.hpp"
#include "../Biome.hpp"
#include "../../gen/MaxMinNoiseMixer.hpp"

struct MultiNoiseBiomeProvider : BiomeProvider {
    struct Noise {
        int firstOctave;
        std::vector<double> amplitudes;
    };

    std::vector<std::pair<Biome*, Biome::Attributes>> parameters;
    std::unique_ptr<MaxMinNoiseMixer> temperatureNoiseMixer;
    std::unique_ptr<MaxMinNoiseMixer> humidityNoiseMixer;
    std::unique_ptr<MaxMinNoiseMixer> altitudeNoiseMixer;
    std::unique_ptr<MaxMinNoiseMixer> weirdnessNoiseMixer;
    bool useHeightForNoise = false;

    MultiNoiseBiomeProvider(int64_t seed, std::vector<std::pair<Biome*, Biome::Attributes>> attributes, const Noise& temperature, const Noise& humidity, const Noise& altitude, const Noise& weirdness) : parameters{std::move(attributes)} {
        temperatureNoiseMixer = std::make_unique<MaxMinNoiseMixer>(Random::from(seed), temperature.firstOctave, temperature.amplitudes);
        humidityNoiseMixer = std::make_unique<MaxMinNoiseMixer>(Random::from(seed + 1), humidity.firstOctave, humidity.amplitudes);
        altitudeNoiseMixer = std::make_unique<MaxMinNoiseMixer>(Random::from(seed + 2), altitude.firstOctave, altitude.amplitudes);
        weirdnessNoiseMixer = std::make_unique<MaxMinNoiseMixer>(Random::from(seed + 3), weirdness.firstOctave, weirdness.amplitudes);
    }

    Biome *getNoiseBiome(int x, int y, int z) override;
};