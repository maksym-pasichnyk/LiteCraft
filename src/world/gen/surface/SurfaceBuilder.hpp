#pragma once

#include "ConfiguredSurfaceBuilder.hpp"
#include <block/BlockData.hpp>
#include <util/Registry.hpp>

#include <memory>

struct Random;
struct Chunk;
struct Biome;

struct SurfaceBuilder {
    static Registry<SurfaceBuilder> builders;

    static SurfaceBuilder* Noop;
    static SurfaceBuilder* Default;
    static SurfaceBuilder* Mountain;
    static SurfaceBuilder* ShatteredSavanna;
    static SurfaceBuilder* GravellyMountain;
    static SurfaceBuilder* GiantTreeTaiga;
    static SurfaceBuilder* Swamp;
    static SurfaceBuilder* Badlands;
    static SurfaceBuilder* WoodedBadlands;
    static SurfaceBuilder* ErodedBadlands;
    static SurfaceBuilder* FrozenOcean;
    static SurfaceBuilder* Nether;
    static SurfaceBuilder* NetherForest;
    static SurfaceBuilder* SoulSandValley;
    static SurfaceBuilder* BasaltDeltas;

    static void registerBuilders();

    virtual ~SurfaceBuilder() = default;

    virtual void setSeed(int64_t seed) {}
    virtual void buildSurface(Random& rand, Chunk& chunk, Biome& biome, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int sealevel, SurfaceBuilderConfig config) = 0;
};
