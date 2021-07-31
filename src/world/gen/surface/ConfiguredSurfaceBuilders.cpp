#include "ConfiguredSurfaceBuilders.hpp"

#include "SurfaceBuilder.hpp"

Registry<ConfiguredSurfaceBuilder> ConfiguredSurfaceBuilders::builders{};

ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::BADLANDS;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::BASALT_DELTAS;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::CRIMSON_FOREST;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::DESERT;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::END;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::ERODED_BADLANDS;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::FROZEN_OCEAN;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::FULL_SAND;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::GIANT_TREE_TAIGA;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::GRASS;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::GRAVELLY_MOUNTAIN;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::ICE_SPIKES;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::MOUNTAIN;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::MYCELIUM;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::NETHER;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::NOPE;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::OCEAN_SAND;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::SHATTERED_SAVANNA;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::SOUL_SAND_VALLEY;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::STONE;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::SWAMP;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::WARPED_FOREST;
ConfiguredSurfaceBuilder* ConfiguredSurfaceBuilders::WOODED_BADLANDS;

ConfiguredSurfaceBuilder* configure(std::string name, SurfaceBuilder* builder, const SurfaceBuilderConfig& config) {
    return ConfiguredSurfaceBuilders::builders.add(std::move(name), std::unique_ptr<ConfiguredSurfaceBuilder>(new ConfiguredSurfaceBuilder{ builder, config }));
}

void ConfiguredSurfaceBuilders::configureSurfaceBuilders() {
    BADLANDS = configure("BADLANDS", SurfaceBuilder::Badlands.get(), SurfaceBuilderConfig::RED_SAND_WHITE_TERRACOTTA_GRAVEL_CONFIG);
    BASALT_DELTAS = configure("BASALT_DELTAS", SurfaceBuilder::BasaltDeltas.get(), SurfaceBuilderConfig::BASALT_DELTAS_CONFIG);
    CRIMSON_FOREST = configure("CRIMSON_FOREST", SurfaceBuilder::NetherForest.get(), SurfaceBuilderConfig::crimson_forest_config);
    DESERT = configure("DESERT", SurfaceBuilder::Default.get(), SurfaceBuilderConfig::SAND_SAND_GRAVEL_CONFIG);
    END = configure("END", SurfaceBuilder::Default.get(), SurfaceBuilderConfig::END_STONE_CONFIG);
    ERODED_BADLANDS = configure("ERODED_BADLANDS", SurfaceBuilder::ErodedBadlands.get(), SurfaceBuilderConfig::RED_SAND_WHITE_TERRACOTTA_GRAVEL_CONFIG);
    FROZEN_OCEAN = configure("FROZEN_OCEAN", SurfaceBuilder::FrozenOcean.get(), SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    FULL_SAND = configure("FULL_SAND", SurfaceBuilder::Default.get(), SurfaceBuilderConfig::SAND_CONFIG);
    GIANT_TREE_TAIGA = configure("GIANT_TREE_TAIGA", SurfaceBuilder::GiantTreeTaiga.get(), SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    GRASS = configure("GRASS", SurfaceBuilder::Default.get(), SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    GRAVELLY_MOUNTAIN = configure("GRAVELLY_MOUNTAIN", SurfaceBuilder::GravellyMountain.get(), SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    ICE_SPIKES = configure("ICE_SPIKES", SurfaceBuilder::Default.get(), SurfaceBuilderConfig::SNOW_DIRT_GRAVEL_CONFIG);
    MOUNTAIN = configure("MOUNTAIN", SurfaceBuilder::Mountain.get(), SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    MYCELIUM = configure("MYCELIUM", SurfaceBuilder::Default.get(), SurfaceBuilderConfig::MYCELIUM_DIRT_GRAVEL_CONFIG);
    NETHER = configure("NETHER", SurfaceBuilder::Nether.get(), SurfaceBuilderConfig::NETHERRACK_CONFIG);
    NOPE = configure("NOPE", SurfaceBuilder::Noop.get(), SurfaceBuilderConfig::STONE_STONE_GRAVEL_CONFIG);
    OCEAN_SAND = configure("OCEAN_SAND", SurfaceBuilder::Default.get(), SurfaceBuilderConfig::GRASS_DIRT_SAND_CONFIG);
    SHATTERED_SAVANNA = configure("SHATTERED_SAVANNA", SurfaceBuilder::ShatteredSavanna.get(), SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    SOUL_SAND_VALLEY = configure("SOUL_SAND_VALLEY", SurfaceBuilder::SoulSandValley.get(), SurfaceBuilderConfig::SOUL_SAND__CONFIG);
    STONE = configure("STONE", SurfaceBuilder::Default.get(), SurfaceBuilderConfig::STONE_STONE_GRAVEL_CONFIG);
    SWAMP = configure("SWAMP", SurfaceBuilder::Swamp.get(), SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    WARPED_FOREST = configure("WARPED_FOREST", SurfaceBuilder::NetherForest.get(), SurfaceBuilderConfig::WARPED_FOREST_CONFIG);
    WOODED_BADLANDS = configure("WOODED_BADLANDS", SurfaceBuilder::WoodedBadlands.get(), SurfaceBuilderConfig::RED_SAND_WHITE_TERRACOTTA_GRAVEL_CONFIG);
}
