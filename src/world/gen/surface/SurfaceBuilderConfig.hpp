#pragma once

#include "../../../block/BlockData.hpp"

struct SurfaceBuilderConfig {
    static SurfaceBuilderConfig PODZOL_DIRT_GRAVEL_CONFIG;
    static SurfaceBuilderConfig GRAVEL_CONFIG;
    static SurfaceBuilderConfig GRASS_DIRT_GRAVEL_CONFIG;
    static SurfaceBuilderConfig STONE_STONE_GRAVEL_CONFIG;
    static SurfaceBuilderConfig CORASE_DIRT_DIRT_GRAVEL_CONFIG;
    static SurfaceBuilderConfig SAND_SAND_GRAVEL_CONFIG;
    static SurfaceBuilderConfig GRASS_DIRT_SAND_CONFIG;
    static SurfaceBuilderConfig SNOW_DIRT_GRAVEL_CONFIG;
    static SurfaceBuilderConfig SAND_CONFIG;
    static SurfaceBuilderConfig RED_SAND_WHITE_TERRACOTTA_GRAVEL_CONFIG;
    static SurfaceBuilderConfig MYCELIUM_DIRT_GRAVEL_CONFIG;
    static SurfaceBuilderConfig NETHERRACK_CONFIG;
    static SurfaceBuilderConfig SOUL_SAND__CONFIG;
    static SurfaceBuilderConfig END_STONE_CONFIG;
    static SurfaceBuilderConfig crimson_forest_config;
    static SurfaceBuilderConfig WARPED_FOREST_CONFIG;
    static SurfaceBuilderConfig BASALT_DELTAS_CONFIG;

    static void registerConfigs();

    BlockData top;
    BlockData mid;
    BlockData underWater;
};