#include "ConfiguredSurfaceBuilder.hpp"
#include "SurfaceBuilder.hpp"

void ConfiguredSurfaceBuilder::setSeed(int64_t seed) {
    builder->setSeed(seed);
}

void ConfiguredSurfaceBuilder::buildSurface(SurfaceBuilderContext& ctx) {
    builder->buildSurface(ctx, config);
}
