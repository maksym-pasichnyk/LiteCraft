#include "Structures.hpp"
#include <world/gen/feature/structure/swamp_hut/SwampHutStructure.hpp>
#include <world/gen/feature/structure/mineshaft/MineshaftStructure.hpp>
#include <world/gen/feature/structure/stronghold/StrongholdStructure.hpp>
#include <world/gen/feature/structure/jungle_pyramid/JunglePyramidStructure.hpp>
#include <world/gen/feature/structure/desert_pyramid/DesertPyramidStructure.hpp>

Registry<Structure> Structures::registry{};
std::array<std::vector<Structure*>, 10> Structures::stages{};

Structure* Structures::MINESHAFT = nullptr;
Structure* Structures::SWAMP_HUT = nullptr;
//Structure* Structures::STRONGHOLD = nullptr;
Structure* Structures::JUNGLE_PYRAMID = nullptr;
Structure* Structures::DESERT_PYRAMID = nullptr;

void Structures::registerStructures() {
//    PILLAGER_OUTPOST = create<PillagerOutpostStructure>("pillager_outpost", GenerationStage::Decoration::SURFACE_STRUCTURES);
    MINESHAFT = create<MineshaftStructure>("mineshaft", GenerationStage::Decoration::UNDERGROUND_STRUCTURES);
//    WOODLAND_MANSION = create<WoodlandMansionStructure>("mansion", GenerationStage::Decoration::SURFACE_STRUCTURES);
    JUNGLE_PYRAMID = create<JunglePyramidStructure>("jungle_pyramid", GenerationStage::Decoration::SURFACE_STRUCTURES);
    DESERT_PYRAMID = create<DesertPyramidStructure>("desert_pyramid", GenerationStage::Decoration::SURFACE_STRUCTURES);
//    IGLOO = create<IglooStructure>("igloo", GenerationStage::Decoration::SURFACE_STRUCTURES);
//    RUINED_PORTAL = create<RuinedPortalStructure>("ruined_portal", GenerationStage::Decoration::SURFACE_STRUCTURES);
//    SHIPWRECK = create<ShipwreckStructure>("shipwreck", GenerationStage::Decoration::SURFACE_STRUCTURES);
    SWAMP_HUT = create<SwampHutStructure>("swamp_hut", GenerationStage::Decoration::SURFACE_STRUCTURES);
//    STRONGHOLD = create<StrongholdStructure>("stronghold", GenerationStage::Decoration::STRONGHOLDS);
//    MONUMENT = create<OceanMonumentStructure>("monument", GenerationStage::Decoration::SURFACE_STRUCTURES);
//    OCEAN_RUIN = create<OceanRuinStructure>("ocean_ruin", GenerationStage::Decoration::SURFACE_STRUCTURES);
//    FORTRESS = create<FortressStructure>("fortress", GenerationStage::Decoration::UNDERGROUND_DECORATION);
//    END_CITY = create<EndCityStructure>("endcity", GenerationStage::Decoration::SURFACE_STRUCTURES);
//    BURIED_TREASURE = create<BuriedTreasureStructure>("buried_treasure", GenerationStage::Decoration::UNDERGROUND_STRUCTURES);
//    VILLAGE = create<VillageStructure>("village", GenerationStage::Decoration::SURFACE_STRUCTURES);
//    NETHER_FOSSIL = create<NetherFossilStructure>("nether_fossil", GenerationStage::Decoration::UNDERGROUND_DECORATION);
//    BASTION_REMNANT = create<BastionRemantsStructure>("bastion_remnant", GenerationStage::Decoration::SURFACE_STRUCTURES);
}
