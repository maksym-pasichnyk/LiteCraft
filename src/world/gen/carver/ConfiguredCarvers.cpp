#include "ConfiguredCarvers.hpp"
#include "ConfiguredCarver.hpp"
#include "Carvers.hpp"

#include <Json.hpp>
#include <ResourceManager.hpp>

Registry<ConfiguredCarver> ConfiguredCarvers::carvers{};

template<>
auto Json::From<ConfiguredCarver*>::from(ConfiguredCarver* const& carver) -> Self {
    return ConfiguredCarvers::carvers.name(carver).value();
}

template<>
auto Json::Into<ConfiguredCarver*>::into(const Self& obj) -> Result {
    return ConfiguredCarvers::carvers.get(obj.as_string().value());
}

void ConfiguredCarvers::init() {
    ResourceManager::enumerate("definitions/configured_carvers", [](std::istream& stream) {
        auto o = Json::Read::read(stream).value();

        carvers.add(o.at("name").as_string().value(), std::make_unique<ConfiguredCarver>(ConfiguredCarver{
            .carver = Carvers::carvers.get(o.at("type").as_string().value()).value(),
            .config = o.at("config")
        }));
    });

//    for (const auto& [name, carver] : carvers.objects) {
//        std::ofstream out{fmt::format("definitions/configured_carvers/{}.json", name), std::ios::binary};
//        out << Json{
//            {"name", name},
//            {"type", carver->carver},
//            {"config", carver->config}
//        };
//    }
}
