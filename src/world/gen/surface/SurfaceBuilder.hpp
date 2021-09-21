#pragma once

#include "ConfiguredSurfaceBuilder.hpp"
#include <block/BlockData.hpp>

struct Random;
struct Chunk;
struct Biome;

struct SurfaceBuilder {
    virtual ~SurfaceBuilder() = default;

    virtual void setSeed(int64_t seed) {}
    virtual void buildSurface(Random& rand, Chunk& chunk, Biome& biome, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int sealevel, SurfaceBuilderConfig config) = 0;
};
