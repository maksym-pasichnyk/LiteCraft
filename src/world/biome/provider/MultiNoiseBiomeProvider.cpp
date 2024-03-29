#include "MultiNoiseBiomeProvider.hpp"
#include "../Biomes.hpp"

#include <range/v3/algorithm.hpp>

const MultiNoiseBiomeProvider::Preset MultiNoiseBiomeProvider::Preset::DEFAULT_NETHER_PROVIDER_PRESET {
    [](int64_t seed) -> std::unique_ptr<MultiNoiseBiomeProvider> {
        return std::make_unique<MultiNoiseBiomeProvider>(seed, std::vector<std::pair<Biome*, BiomeAttributes>> {
            {Biomes::findByName("nether_wastes"), BiomeAttributes{0.0F, 0.0F, 0.0F, 0.0F, 0.0F}},
            {Biomes::findByName("soul_sand_valley"), BiomeAttributes{0.0F, -0.5F, 0.0F, 0.0F, 0.0F}},
            {Biomes::findByName("crimson_forest"), BiomeAttributes{0.4F, 0.0F, 0.0F, 0.0F, 0.0F}},
            {Biomes::findByName("warped_forest"), BiomeAttributes{0.0F, 0.5F, 0.0F, 0.0F, 0.375F}},
            {Biomes::findByName("basalt_deltas"), BiomeAttributes{-0.5F, 0.0F, 0.0F, 0.0F, 0.175F}},
        });
    }
};

Biome *MultiNoiseBiomeProvider::getNoiseBiome(int x, int y, int z) {
    const int i = useHeightForNoise ? y : 0;

    const auto attributes = BiomeAttributes{
        static_cast<float>(temperatureNoiseMixer->noiseAt(x, i, z)),
        static_cast<float>(humidityNoiseMixer->noiseAt(x, i, z)),
        static_cast<float>(altitudeNoiseMixer->noiseAt(x, i, z)),
        static_cast<float>(weirdnessNoiseMixer->noiseAt(x, i, z)),
        0.0F
    };

    auto it = ranges::min_element(parameters, [&attributes](const auto &a, const auto &b) -> bool {
        return attributes.getAttributeDifference(a.second) < attributes.getAttributeDifference(b.second);
    });

    return it != parameters.end() ? it->first : Biomes::findByName("the_void");
}
