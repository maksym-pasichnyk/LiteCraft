#include "Structures.hpp"
#include "MineshaftStructure.hpp"

std::map<std::string, std::unique_ptr<Structure>> Structures::registry;
std::array<std::vector<Structure*>, 10> Structures::stages;

Structure* Structures::MINESHAFT;

template <typename T, typename... Args>
inline T* createStructure(std::string name, GenerationStage::Decoration stage, Args&&... args) {
    auto structure = new T(std::forward<Args>(args)...);
    Structures::registry.emplace(std::move(name), structure);
    Structures::stages.at(static_cast<int>(stage)).emplace_back(structure);
    return structure;
}

void Structures::registerStructures() {
//    PILLAGER_OUTPOST = createStructure<PillagerOutpostStructure>("pillager_outpost", GenerationStage::Decoration::SURFACE_STRUCTURES);
    MINESHAFT = createStructure<MineshaftStructure>("mineshaft", GenerationStage::Decoration::UNDERGROUND_STRUCTURES);
//    WOODLAND_MANSION = createStructure<WoodlandMansionStructure>("mansion", GenerationStage::Decoration::SURFACE_STRUCTURES);
//    JUNGLE_PYRAMID = createStructure<JunglePyramidStructure>("jungle_pyramid", GenerationStage::Decoration::SURFACE_STRUCTURES);
//    DESERT_PYRAMID = createStructure<DesertPyramidStructure>("desert_pyramid", GenerationStage::Decoration::SURFACE_STRUCTURES);
//    IGLOO = createStructure<IglooStructure>("igloo", GenerationStage::Decoration::SURFACE_STRUCTURES);
//    RUINED_PORTAL = createStructure<RuinedPortalStructure>("ruined_portal", GenerationStage::Decoration::SURFACE_STRUCTURES);
//    SHIPWRECK = createStructure<ShipwreckStructure>("shipwreck", GenerationStage::Decoration::SURFACE_STRUCTURES);
//    SWAMP_HUT = createStructure<SwampHutStructure>("swamp_hut", GenerationStage::Decoration::SURFACE_STRUCTURES);
//    STRONGHOLD = createStructure<StrongholdStructure>("stronghold", GenerationStage::Decoration::STRONGHOLDS);
//    MONUMENT = createStructure<OceanMonumentStructure>("monument", GenerationStage::Decoration::SURFACE_STRUCTURES);
//    OCEAN_RUIN = createStructure<OceanRuinStructure>("ocean_ruin", GenerationStage::Decoration::SURFACE_STRUCTURES);
//    FORTRESS = createStructure<FortressStructure>("fortress", GenerationStage::Decoration::UNDERGROUND_DECORATION);
//    END_CITY = createStructure<EndCityStructure>("endcity", GenerationStage::Decoration::SURFACE_STRUCTURES);
//    BURIED_TREASURE = createStructure<BuriedTreasureStructure>("buried_treasure", GenerationStage::Decoration::UNDERGROUND_STRUCTURES);
//    VILLAGE = createStructure<VillageStructure>("village", GenerationStage::Decoration::SURFACE_STRUCTURES);
//    NETHER_FOSSIL = createStructure<NetherFossilStructure>("nether_fossil", GenerationStage::Decoration::UNDERGROUND_DECORATION);
//    BASTION_REMNANT = createStructure<BastionRemantsStructure>("bastion_remnant", GenerationStage::Decoration::SURFACE_STRUCTURES);
}
