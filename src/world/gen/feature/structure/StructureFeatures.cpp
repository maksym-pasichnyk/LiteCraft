#include "StructureFeatures.hpp"
#include "Structures.hpp"
#include "Structure.hpp"

#include <configs.hpp>
#include <resource_manager.hpp>

Registry<StructureFeature> StructureFeatures::registry{};

void StructureFeatures::init(ResourceManager& resources) {
    resources.enumerate("definitions/configured_structure_features", [](std::istream& stream) {
        auto o = Json::Read::read(stream).value();
        auto structure = Structures::registry.get(o.at("type").to_string()).value();
        auto config = structure->deserialize(o.at("config")).value();

        registry.add(o.at("name").to_string(), std::make_unique<StructureFeature>(StructureFeature{
            .structure = structure,
            .config = config
        }));
    });

//    for (auto&& [name, structure] : registry.objects) {
//        std::ofstream out{fmt::format("definitions/configured_structure_features/{}.json", name), std::ios::binary};
//        out << Json{
//            {"name", name},
//            {"type", structure->structure},
//            {"config", structure->config}
//        };
//    }
}
