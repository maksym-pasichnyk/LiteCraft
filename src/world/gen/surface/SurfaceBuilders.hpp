#pragma once

#include <util/Registry.hpp>

struct SurfaceBuilder;
struct SurfaceBuilders {
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

    template <typename T, typename... Args>
    static auto create(std::string name, Args&&... args) -> SurfaceBuilder* {
        return builders.add(std::move(name), std::make_unique<T>(std::forward<Args>(args)...));
    }

    static void init();
};