#include "SurfaceBuilderConfig.hpp"

SurfaceBuilderConfig SurfaceBuilderConfig::PODZOL_DIRT_GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfig::GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfig::STONE_STONE_GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfig::CORASE_DIRT_DIRT_GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfig::SAND_SAND_GRAVEL_CONFIG{};
SurfaceBuilderConfig SurfaceBuilderConfig::GRASS_DIRT_SAND_CONFIG{};
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
    const BlockData GRASS_BLOCK{Block::grass->id, 0};
    const BlockData DIRT{Block::dirt->id, 0};
    const BlockData COARSE_DIRT{Block::dirt->id, 1};
    const BlockData PODZOL{Block::podzol->id, 0};
    const BlockData MYCELIUM{Block::mycelium->id, 0};
    const BlockData GRAVEL{Block::gravel->id, 0};
    const BlockData STONE{Block::stone->id, 0};
    const BlockData SAND{Block::sand->id, 0};
    const BlockData RED_SAND{Block::sand->id, 1};
    const BlockData WHITE_TERRACOTTA{Block::white_glazed_terracotta->id, 0};
    const BlockData NETHERRACK{Block::netherrack->id, 0};
    const BlockData SOUL_SAND{Block::soul_sand->id, 0};
    const BlockData END_STONE{Block::end_stone->id, 0};
//    const BlockData CRIMSON_NYLIUM{BlockIDs::, 0};
//    const BlockData END_STONE{BlockIDs::end_stone, 0};
//    const BlockData END_STONE{BlockIDs::end_stone, 0};

    PODZOL_DIRT_GRAVEL_CONFIG = SurfaceBuilderConfig{PODZOL, DIRT, GRAVEL};
    GRAVEL_CONFIG = SurfaceBuilderConfig{GRAVEL, GRAVEL, GRAVEL};
    GRASS_DIRT_GRAVEL_CONFIG = SurfaceBuilderConfig{GRASS_BLOCK, DIRT, GRAVEL};
    STONE_STONE_GRAVEL_CONFIG = SurfaceBuilderConfig{STONE, STONE, GRAVEL};
    CORASE_DIRT_DIRT_GRAVEL_CONFIG = SurfaceBuilderConfig{COARSE_DIRT, DIRT, GRAVEL};
    SAND_SAND_GRAVEL_CONFIG = SurfaceBuilderConfig{SAND, SAND, GRAVEL};
    GRASS_DIRT_SAND_CONFIG = SurfaceBuilderConfig{GRASS_BLOCK, DIRT, SAND};
    SAND_CONFIG = SurfaceBuilderConfig{SAND, SAND, SAND};
    RED_SAND_WHITE_TERRACOTTA_GRAVEL_CONFIG = SurfaceBuilderConfig{RED_SAND, WHITE_TERRACOTTA, GRAVEL};
    MYCELIUM_DIRT_GRAVEL_CONFIG = SurfaceBuilderConfig{MYCELIUM, DIRT, GRAVEL};
    NETHERRACK_CONFIG = SurfaceBuilderConfig{NETHERRACK, NETHERRACK, NETHERRACK};
    SOUL_SAND__CONFIG = SurfaceBuilderConfig{SOUL_SAND, SOUL_SAND, SOUL_SAND};
    END_STONE_CONFIG = SurfaceBuilderConfig{END_STONE, END_STONE, END_STONE};
//    crimson_forest_config = SurfaceBuilderConfig{CRIMSON_NYLIUM, NETHERRACK, NETHER_WART_BLOCK};
//    WARPED_FOREST_CONFIG = SurfaceBuilderConfig{WARPED_NYLIUM, NETHERRACK, WARPED_WART_BLOCK};
//    BASALT_DELTAS_CONFIG = SurfaceBuilderConfig{BLACKSTONE, BASALT, MAGMA_BLOCK};
}