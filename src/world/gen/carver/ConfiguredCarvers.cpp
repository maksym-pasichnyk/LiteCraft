#include "ConfiguredCarvers.hpp"
#include "ConfiguredCarver.hpp"
#include "Carvers.hpp"

#include <ResourceManager.hpp>
#include <configs.hpp>

Registry<ConfiguredCarver> ConfiguredCarvers::carvers{};

void ConfiguredCarvers::init(ResourceManager& resources) {
    resources.enumerate("definitions/configured_carvers", [](std::istream& stream) {
        auto o = Json::Read::read(stream).value();

        carvers.add(o.at("name").to_string(), std::make_unique<ConfiguredCarver>(ConfiguredCarver{
            .carver = Carvers::carvers.get(o.at("type").to_string()).value(),
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
