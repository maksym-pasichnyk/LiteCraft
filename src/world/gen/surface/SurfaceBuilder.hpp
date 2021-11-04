#pragma once

#include "ConfiguredSurfaceBuilder.hpp"
#include <block/BlockData.hpp>
#include <glm/vec3.hpp>

struct Random;
struct Chunk;
struct Biome;

struct SurfaceBuilderContext {
    Random& random;
    Chunk& chunk;
    Biome& biome;
    BlockPos pos;
    double noise;
    BlockData block;
    BlockData fluid;
    int seaLevel;

    auto getLocalX() const -> int {
        return pos.x & 15;
    }

    auto getLocalZ() const -> int {
        return pos.z & 15;
    }
};

struct SurfaceBuilder {
    virtual ~SurfaceBuilder() = default;

    virtual void setSeed(int64_t seed) {}
    virtual void buildSurface(SurfaceBuilderContext& ctx, const SurfaceBuilderConfig& config) = 0;
};
