#pragma once

#include "ConfiguredSurfaceBuilder.hpp"
#include "../../../block/BlockData.hpp"

#include <memory>

struct Random;
struct Chunk;

struct SurfaceBuilder {
    static std::unique_ptr<SurfaceBuilder> Noop;
    static std::unique_ptr<SurfaceBuilder> Default;
    static std::unique_ptr<SurfaceBuilder> Mountain;
    static std::unique_ptr<SurfaceBuilder> ShatteredSavanna;
    static std::unique_ptr<SurfaceBuilder> GravellyMountain;
    static std::unique_ptr<SurfaceBuilder> GiantTreeTaiga;
    static std::unique_ptr<SurfaceBuilder> Swamp;
    static std::unique_ptr<SurfaceBuilder> Badlands;
    static std::unique_ptr<SurfaceBuilder> WoodedBadlands;
    static std::unique_ptr<SurfaceBuilder> ErodedBadlands;
    static std::unique_ptr<SurfaceBuilder> FrozenOcean;
    static std::unique_ptr<SurfaceBuilder> Nether;
    static std::unique_ptr<SurfaceBuilder> NetherForest;
    static std::unique_ptr<SurfaceBuilder> SoulSandValley;
    static std::unique_ptr<SurfaceBuilder> BasaltDeltas;

    static void registerBuilders();

    virtual ~SurfaceBuilder() = default;

    ConfiguredSurfaceBuilder withConfig(SurfaceBuilderConfig config) {
        return { this, config };
    }

    virtual void setSeed(int64_t seed) {}
    virtual void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int sealevel, SurfaceBuilderConfig config) = 0;
};
