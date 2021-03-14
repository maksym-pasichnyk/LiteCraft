#pragma once

#include <cstdint>

struct Biome;
struct BiomeReader;

using BiomeMagnifier = Biome* (*)(int64_t seed, int x, int y, int z, BiomeReader& biomeReader);

