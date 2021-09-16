#include "ConfiguredSurfaceBuilders.hpp"
#include "SurfaceBuilder.hpp"

#include <fstream>
#include <configs.hpp>
#include <block/Block.hpp>
#include <block/Blocks.hpp>

template<>
struct Json::Serialize<BlockData> {
    static auto to_json(const BlockData &state) -> Json {
        return Blocks::blocks.name(state.getBlock()).value();

//        return {
//            {"name", Blocks::blocks.name(state.getBlock()).value() }
//        };
    }
};

template<>
struct Json::Deserialize<BlockData> {
    static auto from_json(const Json& obj) -> std::optional<BlockData> {
        if (obj.is_string()) {
            return Blocks::blocks.get(obj.to_string()).value()->getDefaultState();
        }
        auto&& o = obj.to_object();
        return Blocks::blocks.get(o.at("name").to_string()).value()->getDefaultState();
    }
};


template<>
struct Json::Serialize<SurfaceBuilderConfig> {
    static auto to_json(const SurfaceBuilderConfig &config) -> Json {
        return {
            {"top_material", config.top},
            {"under_material", config.mid},
            {"underwater_material", config.underWater}
        };
    }
};

template<>
struct Json::Deserialize<SurfaceBuilderConfig> {
    static auto from_json(const Json& obj) -> std::optional<SurfaceBuilderConfig> {
        auto&& o = obj.to_object();
        return SurfaceBuilderConfig{
            .top = o.at("top_material"),
            .mid = o.at("under_material"),
            .underWater = o.at("underwater_material")
        };
    }
};

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
    return ConfiguredSurfaceBuilders::builders.add(std::move(name), std::make_unique<ConfiguredSurfaceBuilder>(ConfiguredSurfaceBuilder{ builder, config }));
}

void ConfiguredSurfaceBuilders::init() {
    BADLANDS = configure("badlands", SurfaceBuilder::Badlands, SurfaceBuilderConfig::RED_SAND_WHITE_TERRACOTTA_GRAVEL_CONFIG);
    BASALT_DELTAS = configure("basalt_deltas", SurfaceBuilder::BasaltDeltas, SurfaceBuilderConfig::BASALT_DELTAS_CONFIG);
    CRIMSON_FOREST = configure("crimson_forest", SurfaceBuilder::NetherForest, SurfaceBuilderConfig::crimson_forest_config);
    DESERT = configure("desert", SurfaceBuilder::Default, SurfaceBuilderConfig::SAND_SAND_GRAVEL_CONFIG);
    END = configure("end", SurfaceBuilder::Default, SurfaceBuilderConfig::END_STONE_CONFIG);
    ERODED_BADLANDS = configure("eroded_badlands", SurfaceBuilder::ErodedBadlands, SurfaceBuilderConfig::RED_SAND_WHITE_TERRACOTTA_GRAVEL_CONFIG);
    FROZEN_OCEAN = configure("frozen_ocean", SurfaceBuilder::FrozenOcean, SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    FULL_SAND = configure("full_sand", SurfaceBuilder::Default, SurfaceBuilderConfig::SAND_CONFIG);
    GIANT_TREE_TAIGA = configure("giant_tree_taiga", SurfaceBuilder::GiantTreeTaiga, SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    GRASS = configure("grass", SurfaceBuilder::Default, SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    GRAVELLY_MOUNTAIN = configure("gravelly_mountain", SurfaceBuilder::GravellyMountain, SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    ICE_SPIKES = configure("ice_spikes", SurfaceBuilder::Default, SurfaceBuilderConfig::SNOW_DIRT_GRAVEL_CONFIG);
    MOUNTAIN = configure("mountain", SurfaceBuilder::Mountain, SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    MYCELIUM = configure("mycelium", SurfaceBuilder::Default, SurfaceBuilderConfig::MYCELIUM_DIRT_GRAVEL_CONFIG);
    NETHER = configure("nether", SurfaceBuilder::Nether, SurfaceBuilderConfig::NETHERRACK_CONFIG);
    NOPE = configure("nope", SurfaceBuilder::Noop, SurfaceBuilderConfig::STONE_STONE_GRAVEL_CONFIG);
    OCEAN_SAND = configure("ocean_sand", SurfaceBuilder::Default, SurfaceBuilderConfig::GRASS_DIRT_SAND_CONFIG);
    SHATTERED_SAVANNA = configure("shattered_savanna", SurfaceBuilder::ShatteredSavanna, SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    SOUL_SAND_VALLEY = configure("soul_sand_valley", SurfaceBuilder::SoulSandValley, SurfaceBuilderConfig::SOUL_SAND__CONFIG);
    STONE = configure("stone", SurfaceBuilder::Default, SurfaceBuilderConfig::STONE_STONE_GRAVEL_CONFIG);
    SWAMP = configure("swamp", SurfaceBuilder::Swamp, SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    WARPED_FOREST = configure("warped_forest", SurfaceBuilder::NetherForest, SurfaceBuilderConfig::WARPED_FOREST_CONFIG);
    WOODED_BADLANDS = configure("wooded_badlands", SurfaceBuilder::WoodedBadlands, SurfaceBuilderConfig::RED_SAND_WHITE_TERRACOTTA_GRAVEL_CONFIG);

    for (auto&& [name, csb] : builders.objects) {
        std::ofstream out{fmt::format("definitions/configured_surface_builders/{}.json", name), std::ios::binary};
        out << Json{
            {"type", csb->builder},
            {"config", csb->config}
        };
    }
}
