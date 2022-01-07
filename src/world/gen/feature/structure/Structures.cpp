#include "Structures.hpp"

#include <Json.hpp>
#include <world/gen/feature/structure/igloo/Igloo.hpp>
#include <world/gen/feature/structure/village/Village.hpp>
#include <world/gen/feature/structure/end_city/EndCity.hpp>
#include <world/gen/feature/structure/fortress/Fortress.hpp>
#include <world/gen/feature/structure/swamp_hut/SwampHut.hpp>
#include <world/gen/feature/structure/mineshaft/Mineshaft.hpp>
#include <world/gen/feature/structure/shipwreck/Shipwreck.hpp>
#include <world/gen/feature/structure/ocean_ruin/OceanRuin.hpp>
#include <world/gen/feature/structure/stronghold/Stronghold.hpp>
#include <world/gen/feature/structure/ruined_portal/RuinedPortal.hpp>
#include <world/gen/feature/structure/nether_fossil/NetherFossil.hpp>
#include <world/gen/feature/structure/ocean_monument/OceanMonument.hpp>
#include <world/gen/feature/structure/jungle_pyramid/JunglePyramid.hpp>
#include <world/gen/feature/structure/desert_pyramid/DesertPyramid.hpp>
#include <world/gen/feature/structure/bastion_remnant/BastionRemnant.hpp>
#include <world/gen/feature/structure/buried_treasure/BuriedTreasure.hpp>
#include <world/gen/feature/structure/woodland_mansion/WoodlandMansion.hpp>
#include <world/gen/feature/structure/pillager_outpost/PillagerOutpost.hpp>

Registry<Structure> Structures::registry{};
std::array<std::vector<Structure*>, 10> Structures::stages{};

//template<>
//auto Json::From<Structure*>::from(Structure* const& structure) -> Self {
//    return Structures::registry.name(structure).value();
//}
//
//template<>
//auto Json::Into<Structure*>::into(const Self& obj) -> Result {
//    return Structures::registry.get(obj.as_string().value());
//}

static auto emplace(const std::string& name, std::unique_ptr<Structure> structure, GenerationStage::Decoration stage) -> Structure* {
    auto ptr = Structures::registry.add(name, std::move(structure));
    Structures::stages.at(static_cast<size_t>(stage)).emplace_back(ptr);
    return ptr;
}

void Structures::init() {
    emplace("pillager_outpost", PillagerOutpost::create(), GenerationStage::Decoration::SURFACE_STRUCTURES);
    emplace("mineshaft", Mineshaft::create(), GenerationStage::Decoration::UNDERGROUND_STRUCTURES);
    emplace("mansion", WoodlandMansion::create(), GenerationStage::Decoration::SURFACE_STRUCTURES);
    emplace("jungle_pyramid", JunglePyramid::create(), GenerationStage::Decoration::SURFACE_STRUCTURES);
    emplace("desert_pyramid", DesertPyramid::create(), GenerationStage::Decoration::SURFACE_STRUCTURES);
    emplace("igloo", Igloo::create(), GenerationStage::Decoration::SURFACE_STRUCTURES);
    emplace("ruined_portal", RuinedPortal::create(), GenerationStage::Decoration::SURFACE_STRUCTURES);
    emplace("shipwreck", Shipwreck::create(), GenerationStage::Decoration::SURFACE_STRUCTURES);
    emplace("swamp_hut", SwampHut::create(), GenerationStage::Decoration::SURFACE_STRUCTURES);
    emplace("stronghold", Stronghold::create(), GenerationStage::Decoration::STRONGHOLDS);
    emplace("monument", OceanMonument::create(), GenerationStage::Decoration::SURFACE_STRUCTURES);
    emplace("ocean_ruin", OceanRuin::create(), GenerationStage::Decoration::SURFACE_STRUCTURES);
    emplace("fortress", Fortress::create(), GenerationStage::Decoration::UNDERGROUND_DECORATION);
    emplace("endcity", EndCity::create(), GenerationStage::Decoration::SURFACE_STRUCTURES);
    emplace("buried_treasure", BuriedTreasure::create(), GenerationStage::Decoration::UNDERGROUND_STRUCTURES);
    emplace("village", Village::create(), GenerationStage::Decoration::SURFACE_STRUCTURES);
    emplace("nether_fossil", NetherFossil::create(), GenerationStage::Decoration::UNDERGROUND_DECORATION);
    emplace("bastion_remnant", BastionRemnant::create(), GenerationStage::Decoration::SURFACE_STRUCTURES);
}
