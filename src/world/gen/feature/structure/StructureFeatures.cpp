#include "StructureFeatures.hpp"
#include "Structures.hpp"
#include "Structure.hpp"

#include <Json.hpp>
#include <ResourceManager.hpp>

Registry<StructureFeature> StructureFeatures::registry{};

template<>
auto Json::From<StructureFeature*>::from(StructureFeature* const& structure) -> Self {
    return StructureFeatures::registry.name(structure).value();
}

template<>
auto Json::Into<StructureFeature*>::into(const Self& obj) -> Result {
    return StructureFeatures::registry.get(obj.as_string().value());
}

void StructureFeatures::init() {
    ResourceManager::enumerate("definitions/configured_structure_features", [](std::istream& stream) {
        auto o = Json::Read::read(stream).value();
        auto structure = Structures::registry.get(o.at("type").as_string().value()).value();
        auto config = structure->deserialize(o.at("config")).value();

        registry.add(o.at("name").as_string().value(), std::make_unique<StructureFeature>(StructureFeature{
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
