#include "ConfiguredSurfaceBuilders.hpp"
#include "SurfaceBuilders.hpp"

#include <Json.hpp>
#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <ResourceManager.hpp>

Registry<ConfiguredSurfaceBuilder> ConfiguredSurfaceBuilders::builders{};

template<>
auto Json::From<ConfiguredSurfaceBuilder*>::from(ConfiguredSurfaceBuilder* const& builder) -> Self {
    return ConfiguredSurfaceBuilders::builders.name(builder).value();
}

template<>
auto Json::Into<ConfiguredSurfaceBuilder*>::into(const Self& obj) -> Result {
    return ConfiguredSurfaceBuilders::builders.get(obj.as_string().value());
}

void ConfiguredSurfaceBuilders::init(ResourceManager& resources) {
    resources.enumerate("definitions/configured_surface_builders", [](std::istream& stream) {
        auto o = Json::Read::read(stream).value();

        builders.add(o.at("name").as_string().value(), std::make_unique<ConfiguredSurfaceBuilder>(ConfiguredSurfaceBuilder{
            .builder = SurfaceBuilders::builders.get(o.at("type").as_string().value()).value(),
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
