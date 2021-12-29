#include "Structures.hpp"

#include <Json.hpp>
#include <world/gen/feature/structure/igloo/IglooStructure.hpp>
#include <world/gen/feature/structure/village/VillageStructure.hpp>
#include <world/gen/feature/structure/end_city/EndCityStructure.hpp>
#include <world/gen/feature/structure/fortress/FortressStructure.hpp>
#include <world/gen/feature/structure/swamp_hut/SwampHutStructure.hpp>
#include <world/gen/feature/structure/mineshaft/MineshaftStructure.hpp>
#include <world/gen/feature/structure/shipwreck/ShipwreckStructure.hpp>
#include <world/gen/feature/structure/ocean_ruin/OceanRuinStructure.hpp>
#include <world/gen/feature/structure/stronghold/StrongholdStructure.hpp>
#include <world/gen/feature/structure/ruined_portal/RuinedPortalStructure.hpp>
#include <world/gen/feature/structure/nether_fossil/NetherFossilStructure.hpp>
#include <world/gen/feature/structure/ocean_monument/OceanMonumentStructure.hpp>
#include <world/gen/feature/structure/jungle_pyramid/JunglePyramidStructure.hpp>
#include <world/gen/feature/structure/desert_pyramid/DesertPyramidStructure.hpp>
#include <world/gen/feature/structure/bastion_remnant/BastionRemnantStructure.hpp>
#include <world/gen/feature/structure/buried_treasure/BuriedTreasureStructure.hpp>
#include <world/gen/feature/structure/woodland_mansion/WoodlandMansionStructure.hpp>
#include <world/gen/feature/structure/pillager_outpost/PillagerOutpostStructure.hpp>

Registry<Structure> Structures::registry{};
std::array<std::vector<Structure*>, 10> Structures::stages{};

template<>
auto Json::From<Structure*>::from(Structure* const& structure) -> Self {
    return Structures::registry.name(structure).value();
}

template<>
auto Json::Into<Structure*>::into(const Self& obj) -> Result {
    return Structures::registry.get(obj.as_string().value());
}

void Structures::init() {
    create<PillagerOutpostStructure>("pillager_outpost", GenerationStage::Decoration::SURFACE_STRUCTURES);
    create<MineshaftStructure>("mineshaft", GenerationStage::Decoration::UNDERGROUND_STRUCTURES);
    create<WoodlandMansionStructure>("mansion", GenerationStage::Decoration::SURFACE_STRUCTURES);
    create<JunglePyramidStructure>("jungle_pyramid", GenerationStage::Decoration::SURFACE_STRUCTURES);
    create<DesertPyramidStructure>("desert_pyramid", GenerationStage::Decoration::SURFACE_STRUCTURES);
    create<IglooStructure>("igloo", GenerationStage::Decoration::SURFACE_STRUCTURES);
    create<RuinedPortalStructure>("ruined_portal", GenerationStage::Decoration::SURFACE_STRUCTURES);
    create<ShipwreckStructure>("shipwreck", GenerationStage::Decoration::SURFACE_STRUCTURES);
    create<SwampHutStructure>("swamp_hut", GenerationStage::Decoration::SURFACE_STRUCTURES);
    create<StrongholdStructure>("stronghold", GenerationStage::Decoration::STRONGHOLDS);
    create<OceanMonumentStructure>("monument", GenerationStage::Decoration::SURFACE_STRUCTURES);
    create<OceanRuinStructure>("ocean_ruin", GenerationStage::Decoration::SURFACE_STRUCTURES);
    create<FortressStructure>("fortress", GenerationStage::Decoration::UNDERGROUND_DECORATION);
    create<EndCityStructure>("endcity", GenerationStage::Decoration::SURFACE_STRUCTURES);
    create<BuriedTreasureStructure>("buried_treasure", GenerationStage::Decoration::UNDERGROUND_STRUCTURES);
    create<VillageStructure>("village", GenerationStage::Decoration::SURFACE_STRUCTURES);
    create<NetherFossilStructure>("nether_fossil", GenerationStage::Decoration::UNDERGROUND_DECORATION);
    create<BastionRemnantStructure>("bastion_remnant", GenerationStage::Decoration::SURFACE_STRUCTURES);
}
