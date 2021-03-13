#include <algorithm>
#include "MultiNoiseBiomeProvider.hpp"

//std::vector<std::pair<Biome*, Biome::Attributes>> NETHER {
//        {/*Biomes::NETHER_WASTES*/nullptr, Biome::Attributes{0.0F, 0.0F, 0.0F, 0.0F, 0.0F}},
//        {/*Biomes::SOUL_SAND_VALLEY*/nullptr, Biome::Attributes{0.0F, -0.5F, 0.0F, 0.0F, 0.0F}},
//        {/*Biomes::CRIMSON_FOREST*/nullptr, Biome::Attributes{0.4F, 0.0F, 0.0F, 0.0F, 0.0F}},
//        {/*Biomes::WARPED_FOREST*/nullptr, Biome::Attributes{0.0F, 0.5F, 0.0F, 0.0F, 0.375F}},
//        {/*Biomes::BASALT_DELTAS*/nullptr, Biome::Attributes{-0.5F, 0.0F, 0.0F, 0.0F, 0.175F}},
//};

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

    return it != parameters.end() ? it->first : /*Biomes::THE_VOID*/nullptr;
}
