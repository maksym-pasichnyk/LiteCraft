#pragma once

#include "ConfiguredSurfaceBuilder.hpp"

#include <util/Registry.hpp>
#include <memory>
#include <map>

struct ConfiguredSurfaceBuilders {
    static Registry<ConfiguredSurfaceBuilder> builders;

    static ConfiguredSurfaceBuilder* BADLANDS;
    static ConfiguredSurfaceBuilder* BASALT_DELTAS;
    static ConfiguredSurfaceBuilder* CRIMSON_FOREST;
    static ConfiguredSurfaceBuilder* DESERT;
    static ConfiguredSurfaceBuilder* END;
    static ConfiguredSurfaceBuilder* ERODED_BADLANDS;
    static ConfiguredSurfaceBuilder* FROZEN_OCEAN;
    static ConfiguredSurfaceBuilder* FULL_SAND;
    static ConfiguredSurfaceBuilder* GIANT_TREE_TAIGA;
    static ConfiguredSurfaceBuilder* GRASS;
    static ConfiguredSurfaceBuilder* GRAVELLY_MOUNTAIN;
    static ConfiguredSurfaceBuilder* ICE_SPIKES;
    static ConfiguredSurfaceBuilder* MOUNTAIN;
    static ConfiguredSurfaceBuilder* MYCELIUM;
    static ConfiguredSurfaceBuilder* NETHER;
    static ConfiguredSurfaceBuilder* NOPE;
    static ConfiguredSurfaceBuilder* OCEAN_SAND;
    static ConfiguredSurfaceBuilder* SHATTERED_SAVANNA;
    static ConfiguredSurfaceBuilder* SOUL_SAND_VALLEY;
    static ConfiguredSurfaceBuilder* STONE;
    static ConfiguredSurfaceBuilder* SWAMP;
    static ConfiguredSurfaceBuilder* WARPED_FOREST;
    static ConfiguredSurfaceBuilder* WOODED_BADLANDS;

    static void init();
};