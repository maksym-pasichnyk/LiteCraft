#include "ConfiguredSurfaceBuilders.hpp"
#include "SurfaceBuilders.hpp"

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

void ConfiguredSurfaceBuilders::init() {
    configure("badlands", SurfaceBuilders::Badlands, SurfaceBuilderConfig::RED_SAND_WHITE_TERRACOTTA_GRAVEL_CONFIG);
    configure("basalt_deltas", SurfaceBuilders::BasaltDeltas, SurfaceBuilderConfig::BASALT_DELTAS_CONFIG);
    configure("crimson_forest", SurfaceBuilders::NetherForest, SurfaceBuilderConfig::crimson_forest_config);
    configure("desert", SurfaceBuilders::Default, SurfaceBuilderConfig::SAND_SAND_GRAVEL_CONFIG);
    configure("end", SurfaceBuilders::Default, SurfaceBuilderConfig::END_STONE_CONFIG);
    configure("eroded_badlands", SurfaceBuilders::ErodedBadlands, SurfaceBuilderConfig::RED_SAND_WHITE_TERRACOTTA_GRAVEL_CONFIG);
    configure("frozen_ocean", SurfaceBuilders::FrozenOcean, SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    configure("full_sand", SurfaceBuilders::Default, SurfaceBuilderConfig::SAND_CONFIG);
    configure("giant_tree_taiga", SurfaceBuilders::GiantTreeTaiga, SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    configure("grass", SurfaceBuilders::Default, SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    configure("gravelly_mountain", SurfaceBuilders::GravellyMountain, SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    configure("ice_spikes", SurfaceBuilders::Default, SurfaceBuilderConfig::SNOW_DIRT_GRAVEL_CONFIG);
    configure("mountain", SurfaceBuilders::Mountain, SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    configure("mycelium", SurfaceBuilders::Default, SurfaceBuilderConfig::MYCELIUM_DIRT_GRAVEL_CONFIG);
    configure("nether", SurfaceBuilders::Nether, SurfaceBuilderConfig::NETHERRACK_CONFIG);
    configure("nope", SurfaceBuilders::Noop, SurfaceBuilderConfig::STONE_STONE_GRAVEL_CONFIG);
    configure("ocean_sand", SurfaceBuilders::Default, SurfaceBuilderConfig::GRASS_DIRT_SAND_CONFIG);
    configure("shattered_savanna", SurfaceBuilders::ShatteredSavanna, SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    configure("soul_sand_valley", SurfaceBuilders::SoulSandValley, SurfaceBuilderConfig::SOUL_SAND__CONFIG);
    configure("stone", SurfaceBuilders::Default, SurfaceBuilderConfig::STONE_STONE_GRAVEL_CONFIG);
    configure("swamp", SurfaceBuilders::Swamp, SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
    configure("warped_forest", SurfaceBuilders::NetherForest, SurfaceBuilderConfig::WARPED_FOREST_CONFIG);
    configure("wooded_badlands", SurfaceBuilders::WoodedBadlands, SurfaceBuilderConfig::RED_SAND_WHITE_TERRACOTTA_GRAVEL_CONFIG);

    for (auto&& [name, csb] : builders.objects) {
        std::ofstream out{fmt::format("definitions/configured_surface_builders/{}.json", name), std::ios::binary};
        out << Json{
            {"type", csb->builder},
            {"config", csb->config}
        };
    }
}
