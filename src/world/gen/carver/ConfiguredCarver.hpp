#pragma once

#include "WorldCarver.hpp"
#include "../../../util/Random.hpp"

#include <cstdint>

struct Chunk;
struct Random;

struct ProbabilityConfig {
    float probability;
};

struct ConfiguredCarver {
    ProbabilityConfig config;
    WorldCarver* carver;

    bool shouldCarve(Random& rand, int32_t x, int32_t z) {
        auto v = rand.nextFloat();
        return v <= config.probability;
    }

    bool carveRegion(Chunk& chunk, const BiomeReadFn& getBiome, Random& rand, int32_t seaLevel, int32_t xoffset, int32_t zoffset, int32_t chunkx, int32_t chunkz/*, BitSet carvingMask*/) {
        return carver->carveRegion(chunk, getBiome, rand, seaLevel, xoffset, zoffset, chunkx, chunkz/*, carvingMask*/);
    }
};