#include <algorithm>
#include "MultiNoiseBiomeProvider.hpp"

const MultiNoiseBiomeProvider::Preset MultiNoiseBiomeProvider::Preset::DEFAULT_NETHER_PROVIDER_PRESET {
    [](int64_t seed) -> std::unique_ptr<MultiNoiseBiomeProvider> {
        return std::make_unique<MultiNoiseBiomeProvider>(seed, std::vector<std::pair<Biome*, Biome::Attributes>> {
            {Biome::NETHER_WASTES, Biome::Attributes{0.0F, 0.0F, 0.0F, 0.0F, 0.0F}},
            {Biome::SOUL_SAND_VALLEY, Biome::Attributes{0.0F, -0.5F, 0.0F, 0.0F, 0.0F}},
            {Biome::CRIMSON_FOREST, Biome::Attributes{0.4F, 0.0F, 0.0F, 0.0F, 0.0F}},
            {Biome::WARPED_FOREST, Biome::Attributes{0.0F, 0.5F, 0.0F, 0.0F, 0.375F}},
            {Biome::BASALT_DELTAS, Biome::Attributes{-0.5F, 0.0F, 0.0F, 0.0F, 0.175F}},
        });
    }
};

Biome *MultiNoiseBiomeProvider::getNoiseBiome(int x, int y, int z) {
    const int i = useHeightForNoise ? y : 0;

    const Biome::Attributes attributes{
        static_cast<float>(temperatureNoiseMixer->noiseAt(x, i, z)),
        static_cast<float>(humidityNoiseMixer->noiseAt(x, i, z)),
        static_cast<float>(altitudeNoiseMixer->noiseAt(x, i, z)),
        static_cast<float>(weirdnessNoiseMixer->noiseAt(x, i, z)),
        0.0F
    };

    auto it = std::ranges::min_element(parameters, [&attributes](const auto &a, const auto &b) -> bool {
        return attributes.getAttributeDifference(a.second) < attributes.getAttributeDifference(b.second);
    });

    return it != parameters.end() ? it->first : Biome::THE_VOID;
}
