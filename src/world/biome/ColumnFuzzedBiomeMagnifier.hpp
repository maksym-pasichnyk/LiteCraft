#pragma once

#include <cstdint>

struct Biome;
struct BiomeReader;

struct ColumnFuzzedBiomeMagnifier {
    static Biome* getBiome(int64_t seed, int x, int y, int z, BiomeReader& biomeReader);
};