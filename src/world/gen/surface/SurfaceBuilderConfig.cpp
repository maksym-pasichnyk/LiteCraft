#include "SurfaceBuilderConfig.hpp"
#include "../../../block/Block.hpp"
#include "../../../block/Blocks.hpp"

SurfaceBuilderConfig SurfaceBuilderConfig::PODZOL_DIRT_GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfig::GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfig::STONE_STONE_GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfig::CORASE_DIRT_DIRT_GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfig::SAND_SAND_GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfig::GRASS_DIRT_SAND_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfig::SNOW_DIRT_GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfig::SAND_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfig::RED_SAND_WHITE_TERRACOTTA_GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfig::MYCELIUM_DIRT_GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfig::NETHERRACK_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfig::SOUL_SAND__CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfig::END_STONE_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfig::crimson_forest_config{};
SurfaceBuilderConfig SurfaceBuilderConfig::WARPED_FOREST_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfig::BASALT_DELTAS_CONFIG{};

void SurfaceBuilderConfig::registerConfigs() {
    const BlockData GRASS_BLOCK = Blocks::GRASS_BLOCK->getDefaultState();
    const BlockData DIRT = Blocks::DIRT->getDefaultState();
    const BlockData COARSE_DIRT = Blocks::DIRT->getStateWithMeta(1);
    const BlockData PODZOL = Blocks::PODZOL->getDefaultState();
    const BlockData MYCELIUM = Blocks::MYCELIUM->getDefaultState();
    const BlockData GRAVEL = Blocks::GRAVEL->getDefaultState();
    const BlockData STONE = Blocks::STONE->getDefaultState();
    const BlockData SAND = Blocks::SAND->getDefaultState();
    const BlockData RED_SAND = Blocks::SAND->getStateWithMeta(1);
    const BlockData SNOW = Blocks::SNOW->getDefaultState();
    const BlockData WHITE_TERRACOTTA = Blocks::TERRACOTTA->getStateWithMeta(0);//Blocks2::stained_hardened_clay->getDefaultState();
    const BlockData NETHERRACK = Blocks::NETHERRACK->getDefaultState();
    const BlockData SOUL_SAND = Blocks::SOUL_SAND->getDefaultState();
    const BlockData END_STONE = Blocks::END_STONE->getDefaultState();
    const BlockData CRIMSON_NYLIUM = Blocks::CRIMSON_NYLIUM->getDefaultState();
    const BlockData WARPED_NYLIUM = Blocks::WARPED_NYLIUM->getDefaultState();
    const BlockData NETHER_WART_BLOCK = Blocks::NETHER_WART_BLOCK->getDefaultState();
    const BlockData WARPED_WART_BLOCK = Blocks::WARPED_WART_BLOCK->getDefaultState();
    const BlockData BLACKSTONE = Blocks::BLACKSTONE->getDefaultState();
    const BlockData BASALT = Blocks::BASALT->getDefaultState();
    const BlockData MAGMA_BLOCK = Blocks::MAGMA_BLOCK->getDefaultState();

    PODZOL_DIRT_GRAVEL_CONFIG = SurfaceBuilderConfig{PODZOL, DIRT, GRAVEL};
    GRAVEL_CONFIG = SurfaceBuilderConfig{GRAVEL, GRAVEL, GRAVEL};
    GRASS_DIRT_GRAVEL_CONFIG = SurfaceBuilderConfig{GRASS_BLOCK, DIRT, GRAVEL};
    STONE_STONE_GRAVEL_CONFIG = SurfaceBuilderConfig{STONE, STONE, GRAVEL};
    CORASE_DIRT_DIRT_GRAVEL_CONFIG = SurfaceBuilderConfig{COARSE_DIRT, DIRT, GRAVEL};
    SAND_SAND_GRAVEL_CONFIG = SurfaceBuilderConfig{SAND, SAND, GRAVEL};
    GRASS_DIRT_SAND_CONFIG = SurfaceBuilderConfig{GRASS_BLOCK, DIRT, SAND};
    SNOW_DIRT_GRAVEL_CONFIG = SurfaceBuilderConfig{SNOW, DIRT, SAND};
    SAND_CONFIG = SurfaceBuilderConfig{SAND, SAND, SAND};
    RED_SAND_WHITE_TERRACOTTA_GRAVEL_CONFIG = SurfaceBuilderConfig{RED_SAND, WHITE_TERRACOTTA, GRAVEL};
    MYCELIUM_DIRT_GRAVEL_CONFIG = SurfaceBuilderConfig{MYCELIUM, DIRT, GRAVEL};
    NETHERRACK_CONFIG = SurfaceBuilderConfig{NETHERRACK, NETHERRACK, NETHERRACK};
    SOUL_SAND__CONFIG = SurfaceBuilderConfig{SOUL_SAND, SOUL_SAND, SOUL_SAND};
    END_STONE_CONFIG = SurfaceBuilderConfig{END_STONE, END_STONE, END_STONE};
    crimson_forest_config = SurfaceBuilderConfig{CRIMSON_NYLIUM, NETHERRACK, NETHER_WART_BLOCK};
    WARPED_FOREST_CONFIG = SurfaceBuilderConfig{WARPED_NYLIUM, NETHERRACK, WARPED_WART_BLOCK};
    BASALT_DELTAS_CONFIG = SurfaceBuilderConfig{BLACKSTONE, BASALT, MAGMA_BLOCK};
}