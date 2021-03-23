#pragma once

#include "../../biome/BiomeReadFn.hpp"

#include <cstdint>

struct Chunk;
struct Random;
struct WorldCarver;

struct ProbabilityConfig {
    float probability;
};

struct ConfiguredCarver {
    WorldCarver* carver;
    ProbabilityConfig config;

    bool shouldCarve(Random& rand, int32_t x, int32_t z);
    bool carveRegion(Chunk& chunk, const BiomeReadFn& getBiome, Random& rand, int32_t seaLevel, int32_t xoffset, int32_t zoffset, int32_t chunkx, int32_t chunkz/*, BitSet carvingMask*/);
};