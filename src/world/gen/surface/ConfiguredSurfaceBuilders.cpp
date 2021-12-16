#include "ConfiguredSurfaceBuilders.hpp"
#include "SurfaceBuilders.hpp"

#include <ResourceManager.hpp>
#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <configs.hpp>

template<>
struct Json::From<BlockData> {
    static auto from(const BlockData &state) -> Json {
        return Blocks::blocks.name(state.getBlock()).value();

//        return {
//            {"name", Blocks::blocks.name(state.getBlock()).value() }
//        };
    }
};

template<>
struct Json::Into<BlockData> {
    static auto into(const Json& obj) -> std::optional<BlockData> {
        if (obj.is_string()) {
            return Blocks::blocks.get(obj.to_string()).value()->getDefaultState();
        }
        return Blocks::blocks.get(obj.at("name").to_string()).value()->getDefaultState();
    }
};

template<>
struct Json::From<SurfaceBuilderConfig> {
    static auto from(const SurfaceBuilderConfig &config) -> Json {
        return {
            {"top_material", config.top},
            {"under_material", config.mid},
            {"underwater_material", config.underWater}
        };
    }
};

template<>
struct Json::Into<SurfaceBuilderConfig> {
    static auto into(const Json& obj) -> std::optional<SurfaceBuilderConfig> {
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
