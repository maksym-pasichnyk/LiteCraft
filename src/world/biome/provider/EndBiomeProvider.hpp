#pragma once

#include "BiomeProvider.hpp"
#include "../../gen/SimplexNoiseGenerator.hpp"
#include "../../../util/Random.hpp"

#include <memory>
#include <cstdint>

struct EndBiomeProvider : BiomeProvider {
    Biome* theEndBiome;
    Biome* endHighlandsBiome;
    Biome* endMidlandsBiome;
    Biome* smallEndIslandsBiome;
    Biome* endBarrensBiome;

    std::unique_ptr<SimplexNoiseGenerator> generator;

    EndBiomeProvider(int64_t seed, Biome* theEndBiome, Biome* endHighlandsBiome, Biome* endMidlandsBiome, Biome* smallEndIslandsBiome, Biome* endBarrensBiome);

    Biome* getNoiseBiome(int x, int y, int z) override;

    float getRandomNoise(int x, int z);
};