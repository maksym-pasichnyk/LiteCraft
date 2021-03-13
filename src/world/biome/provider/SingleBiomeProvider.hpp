#pragma once

#include "BiomeProvider.hpp"

struct SingleBiomeProvider : BiomeProvider {
    Biome* biome;

    explicit SingleBiomeProvider(Biome* biome) : biome(biome) {}

    Biome* getNoiseBiome(int x, int y, int z) override {
        return biome;
    }
};