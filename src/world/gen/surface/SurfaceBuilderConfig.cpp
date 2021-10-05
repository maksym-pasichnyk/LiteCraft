#include "SurfaceBuilderConfig.hpp"
#include <block/Block.hpp>
#include <block/States.hpp>

SurfaceBuilderConfig SurfaceBuilderConfigs::PODZOL_DIRT_GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfigs::GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfigs::GRASS_DIRT_GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfigs::STONE_STONE_GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfigs::CORASE_DIRT_DIRT_GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfigs::SAND_SAND_GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfigs::GRASS_DIRT_SAND_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfigs::SNOW_DIRT_GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfigs::SAND_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfigs::RED_SAND_WHITE_TERRACOTTA_GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfigs::MYCELIUM_DIRT_GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfigs::NETHERRACK_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfigs::SOUL_SAND__CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfigs::END_STONE_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfigs::crimson_forest_config{};
SurfaceBuilderConfig SurfaceBuilderConfigs::WARPED_FOREST_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfigs::BASALT_DELTAS_CONFIG{};

void SurfaceBuilderConfigs::init() {
    PODZOL_DIRT_GRAVEL_CONFIG = SurfaceBuilderConfig{
        States::PODZOL,
        States::DIRT,
        States::GRAVEL
    };

    GRAVEL_CONFIG = SurfaceBuilderConfig{
        States::GRAVEL,
        States::GRAVEL,
        States::GRAVEL
    };

    GRASS_DIRT_GRAVEL_CONFIG = SurfaceBuilderConfig{
        States::GRASS_BLOCK,
        States::DIRT,
        States::GRAVEL
    };

    STONE_STONE_GRAVEL_CONFIG = SurfaceBuilderConfig{
        States::STONE,
        States::STONE,
        States::GRAVEL
    };

    CORASE_DIRT_DIRT_GRAVEL_CONFIG = SurfaceBuilderConfig{
        States::COARSE_DIRT,
        States::DIRT,
        States::GRAVEL
    };

    SAND_SAND_GRAVEL_CONFIG = SurfaceBuilderConfig{
        States::SAND,
        States::SAND,
        States::GRAVEL
    };

    GRASS_DIRT_SAND_CONFIG = SurfaceBuilderConfig{
        States::GRASS_BLOCK,
        States::DIRT,
        States::SAND
    };

    SNOW_DIRT_GRAVEL_CONFIG = SurfaceBuilderConfig{
        States::SNOW,
        States::DIRT,
        States::SAND
    };

    SAND_CONFIG = SurfaceBuilderConfig{
        States::SAND,
        States::SAND,
        States::SAND
    };

    RED_SAND_WHITE_TERRACOTTA_GRAVEL_CONFIG = SurfaceBuilderConfig{
        States::RED_SAND,
        States::WHITE_TERRACOTTA,
        States::GRAVEL
    };

    MYCELIUM_DIRT_GRAVEL_CONFIG = SurfaceBuilderConfig{
        States::MYCELIUM,
        States::DIRT,
        States::GRAVEL
    };

    NETHERRACK_CONFIG = SurfaceBuilderConfig{
        States::NETHERRACK,
        States::NETHERRACK,
        States::NETHERRACK
    };

    SOUL_SAND__CONFIG = SurfaceBuilderConfig{
        States::SOUL_SAND,
        States::SOUL_SAND,
        States::SOUL_SAND
    };

    END_STONE_CONFIG = SurfaceBuilderConfig{
        States::END_STONE,
        States::END_STONE,
        States::END_STONE
    };

    crimson_forest_config = SurfaceBuilderConfig{
        States::CRIMSON_NYLIUM,
        States::NETHERRACK,
        States::NETHER_WART_BLOCK
    };

    WARPED_FOREST_CONFIG = SurfaceBuilderConfig{
        States::WARPED_NYLIUM,
        States::NETHERRACK,
        States::WARPED_WART_BLOCK
    };

    BASALT_DELTAS_CONFIG = SurfaceBuilderConfig{
        States::BLACKSTONE,
        States::BASALT,
        States::MAGMA_BLOCK
    };
}