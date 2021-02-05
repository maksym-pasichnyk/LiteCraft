#pragma once

#include "SurfaceBuilder.h"

struct Biome;

//struct DefaultSurfaceBuilder : SurfaceBuilder {
//    void buildSurface(Random& rand, Chunk *chunk, Biome* biome, int32_t x, int32_t y, int32_t z, double noise, BlockData defaultBlock, BlockData fluidBlock, int32_t seaLevel, int64_t worldSeed) override {
//
//    }
//
//    void buildSurface(Random& rand, Chunk *chunk, Biome* biome, int32_t xStart, int32_t zStart, int32_t startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData middle, BlockData bottom, int32_t sealevel);
//};