#include "ConfiguredSurfaceBuilders.hpp"

#include "SurfaceBuilder.hpp"

ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::BADLANDS{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::BASALT_DELTAS{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::CRIMSON_FOREST{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::DESERT{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::END{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::ERODED_BADLANDS{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::FROZEN_OCEAN{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::FULL_SAND{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::GIANT_TREE_TAIGA{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::GRASS{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::GRAVELLY_MOUNTAIN{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::ICE_SPIKES{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::MOUNTAIN{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::MYCELIUM{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::NETHER{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::NOPE{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::OCEAN_SAND{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::SHATTERED_SAVANNA{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::SOUL_SAND_VALLEY{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::STONE{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::SWAMP{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::WARPED_FOREST{};
ConfiguredSurfaceBuilder ConfiguredSurfaceBuilders::WOODED_BADLANDS{};

void ConfiguredSurfaceBuilders::configureSurfaceBuilders() {
    BADLANDS = SurfaceBuilder::Badlands->withConfig(SurfaceBuilderConfig::RED_SAND_WHITE_TERRACOTTA_GRAVEL_CONFIG);
    BASALT_DELTAS = SurfaceBuilder::BasaltDeltas->withConfig(SurfaceBuilderConfig::BASALT_DELTAS_CONFIG);
    CRIMSON_FOREST = SurfaceBuilder::NetherForest->withConfig(SurfaceBuilderConfig::crimson_forest_config);
    DESERT = SurfaceBuilder::Default->withConfig(SurfaceBuilderConfig::SAND_SAND_GRAVEL_CONFIG);
    END = SurfaceBuilder::Default->withConfig(SurfaceBuilderConfig::END_STONE_CONFIG);
    ERODED_BADLANDS = SurfaceBuilder::ErodedBadlands->withConfig(SurfaceBuilderConfig::RED_SAND_WHITE_TERRACOTTA_GRAVEL_CONFIG);
    FROZEN_OCEAN = SurfaceBuilder::FrozenOcean->withConfig(SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    FULL_SAND = SurfaceBuilder::Default->withConfig(SurfaceBuilderConfig::SAND_CONFIG);
    GIANT_TREE_TAIGA = SurfaceBuilder::GiantTreeTaiga->withConfig(SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    GRASS = SurfaceBuilder::Default->withConfig(SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    GRAVELLY_MOUNTAIN = SurfaceBuilder::GravellyMountain->withConfig(SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    ICE_SPIKES = SurfaceBuilder::Default->withConfig(SurfaceBuilderConfig::SNOW_DIRT_GRAVEL_CONFIG);
    MOUNTAIN = SurfaceBuilder::Mountain->withConfig(SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    MYCELIUM = SurfaceBuilder::Default->withConfig(SurfaceBuilderConfig::MYCELIUM_DIRT_GRAVEL_CONFIG);
    NETHER = SurfaceBuilder::Nether->withConfig(SurfaceBuilderConfig::NETHERRACK_CONFIG);
    NOPE = SurfaceBuilder::Noop->withConfig(SurfaceBuilderConfig::STONE_STONE_GRAVEL_CONFIG);
    OCEAN_SAND = SurfaceBuilder::Default->withConfig(SurfaceBuilderConfig::GRASS_DIRT_SAND_CONFIG);
    SHATTERED_SAVANNA = SurfaceBuilder::ShatteredSavanna->withConfig(SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    SOUL_SAND_VALLEY = SurfaceBuilder::SoulSandValley->withConfig(SurfaceBuilderConfig::SOUL_SAND__CONFIG);
    STONE = SurfaceBuilder::Default->withConfig(SurfaceBuilderConfig::STONE_STONE_GRAVEL_CONFIG);
    SWAMP = SurfaceBuilder::Swamp->withConfig(SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    WARPED_FOREST = SurfaceBuilder::NetherForest->withConfig(SurfaceBuilderConfig::WARPED_FOREST_CONFIG);
    WOODED_BADLANDS = SurfaceBuilder::WoodedBadlands->withConfig(SurfaceBuilderConfig::RED_SAND_WHITE_TERRACOTTA_GRAVEL_CONFIG);
}
