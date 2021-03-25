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
    const BlockData GRASS_BLOCK = Blocks::grass->getDefaultState();
    const BlockData DIRT = Blocks::dirt->getDefaultState();
    const BlockData COARSE_DIRT = Blocks::dirt->getStateWithMeta(1);
    const BlockData PODZOL = Blocks::podzol->getDefaultState();
    const BlockData MYCELIUM = Blocks::mycelium->getDefaultState();
    const BlockData GRAVEL = Blocks::gravel->getDefaultState();
    const BlockData STONE = Blocks::stone->getDefaultState();
    const BlockData SAND = Blocks::sand->getDefaultState();
    const BlockData RED_SAND = Blocks::sand->getStateWithMeta(1);
    const BlockData SNOW = Blocks::snow->getDefaultState();
    const BlockData WHITE_TERRACOTTA = Blocks::stained_hardened_clay->getDefaultState();
    const BlockData NETHERRACK = Blocks::netherrack->getDefaultState();
    const BlockData SOUL_SAND = Blocks::soul_sand->getDefaultState();
    const BlockData END_STONE = Blocks::end_stone->getDefaultState();
    const BlockData CRIMSON_NYLIUM = Blocks::crimson_nylium->getDefaultState();
    const BlockData WARPED_NYLIUM = Blocks::warped_nylium->getDefaultState();
    const BlockData NETHER_WART_BLOCK = Blocks::nether_wart_block->getDefaultState();
    const BlockData WARPED_WART_BLOCK = Blocks::warped_wart_block->getDefaultState();
    const BlockData BLACKSTONE = Blocks::blackstone->getDefaultState();
    const BlockData BASALT = Blocks::basalt->getDefaultState();
    const BlockData MAGMA_BLOCK = Blocks::magma->getDefaultState();

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