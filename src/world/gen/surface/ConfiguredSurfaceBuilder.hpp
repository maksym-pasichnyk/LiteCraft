#pragma once

#include "SurfaceBuilderConfig.hpp"

#include <mutex>

struct Random;
struct Chunk;
struct Biome;
struct SurfaceBuilder;

struct ConfiguredSurfaceBuilder {
    SurfaceBuilder* builder{};
    SurfaceBuilderConfig config{};

    std::mutex mutex;

    void setSeed(int64_t seed);
    void buildSurface(Random& rand, Chunk& chunk, Biome& biome, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int sealevel);
};