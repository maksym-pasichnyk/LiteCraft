#include "ConfiguredSurfaceBuilder.hpp"
#include "SurfaceBuilder.hpp"

void ConfiguredSurfaceBuilder::setSeed(int64_t seed) {
    builder->setSeed(seed);
}

void ConfiguredSurfaceBuilder::buildSurface(Random &rand, Chunk &chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int sealevel) {
    builder->buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, sealevel, config);
}
