#include "ConfiguredSurfaceBuilders.hpp"
#include "SurfaceBuilders.hpp"

#include <configs.hpp>
#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <resource_manager.hpp>

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

void ConfiguredSurfaceBuilders::init(ResourceManager& resources) {
    resources.enumerate("definitions/configured_surface_builders", [](std::istream& stream) {
        auto o = Json::Read::read(stream).value();

        builders.add(o.at("name").to_string(), std::make_unique<ConfiguredSurfaceBuilder>(ConfiguredSurfaceBuilder{
            .builder = SurfaceBuilders::builders.get(o.at("type").to_string()).value(),
            .config = o.at("config")
        }));
    });

//    for (auto&& [name, csb] : builders.objects) {
//        std::ofstream out{fmt::format("definitions/configured_surface_builders/{}.json", name), std::ios::binary};
//        out << Json{
//            {"name", name},
//            {"type", csb->builder},
//            {"config", csb->config}
//        };
//    }
}
