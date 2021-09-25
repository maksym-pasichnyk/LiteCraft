#include "ConfiguredSurfaceBuilders.hpp"
#include "SurfaceBuilders.hpp"

#include <fstream>
#include <filesystem>
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
        return Blocks::blocks.get(obj.at("name").to_string()).value()->getDefaultState();
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
    for (auto&& entry : std::filesystem::directory_iterator{"definitions/configured_surface_builders"}) {
        if (!entry.is_regular_file()) {
            continue;
        }

        auto o = Json::Read::read(std::ifstream{entry.path(), std::ios::binary}).value();
        auto surface_builder = SurfaceBuilders::builders.get(o.at("type").to_string()).value();
        configure(entry.path().stem().string(), surface_builder, o.at("config"));
    }

//    for (auto&& [name, csb] : builders.objects) {
//        std::ofstream out{fmt::format("definitions/configured_surface_builders/{}.json", name), std::ios::binary};
//        out << Json{
//            {"type", csb->builder},
//            {"config", csb->config}
//        };
//    }
}
