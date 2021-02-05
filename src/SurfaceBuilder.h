#pragma once

#include <src/BlockTable.hpp>
#include <cstdint>

struct Random;
struct Chunk;
struct Biome;

struct SurfaceBuilder {
    virtual void buildSurface(Random& rand, Chunk *chunk, Biome* biome, int32_t x, int32_t y, int32_t z, double noise, BlockData defaultBlock, BlockData fluidBlock, int32_t seaLevel, int64_t worldSeed) = 0;
};
