#pragma once

struct Biome;

struct BiomeProvider {
    virtual ~BiomeProvider() = default;
    virtual Biome* getNoiseBiome(int x, int y, int z) = 0;
};
