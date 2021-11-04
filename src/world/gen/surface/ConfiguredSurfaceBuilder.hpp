#pragma once

#include "SurfaceBuilderConfig.hpp"

#include <mutex>

struct Random;
struct Chunk;
struct Biome;
struct SurfaceBuilder;
struct SurfaceBuilderContext;

struct ConfiguredSurfaceBuilder {
    SurfaceBuilder* builder{};
    SurfaceBuilderConfig config{};

    void setSeed(int64_t seed);
    void buildSurface(SurfaceBuilderContext& ctx);
};