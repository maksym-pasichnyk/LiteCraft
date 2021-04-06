#include "TemperatureModifiers.hpp"
#include "Biome.hpp"

float TemperatureModifiers::none(BlockPos pos, float temperature) {
    return temperature;
}

float TemperatureModifiers::frozen(BlockPos pos, float temperature) {
    const double frozen = Biome::FROZEN_TEMPERATURE_NOISE.noiseAt(
            static_cast<double>(pos.x) * 0.05,
            static_cast<double>(pos.z) * 0.05,
            false) * 7.0;

    const double noise = Biome::INFO_NOISE.noiseAt(
            static_cast<double>(pos.x) * 0.2,
            static_cast<double>(pos.z) * 0.2,
            false);

    if ((frozen + noise) < 0.3) {
        const double d3 = Biome::INFO_NOISE.noiseAt(
                static_cast<double>(pos.x) * 0.09,
                static_cast<double>(pos.z) * 0.09,
                false);

        if (d3 < 0.8) {
            return 0.2F;
        }
    }
    return temperature;
}
