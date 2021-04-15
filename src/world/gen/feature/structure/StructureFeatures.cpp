#include "StructureFeatures.hpp"
#include "Structure.hpp"
#include "Structures.hpp"

std::map<std::string, std::unique_ptr<StructureFeature>> StructureFeatures::registry;

StructureFeature* StructureFeatures::PILLAGER_OUTPOST;
StructureFeature* StructureFeatures::MINESHAFT;
StructureFeature* StructureFeatures::MINESHAFT_BADLANDS;
StructureFeature* StructureFeatures::MANSION;
StructureFeature* StructureFeatures::JUNGLE_PYRAMID;
StructureFeature* StructureFeatures::DESERT_PYRAMID;
StructureFeature* StructureFeatures::IGLOO;
StructureFeature* StructureFeatures::SHIPWRECK;
StructureFeature* StructureFeatures::SHIPWRECK_BEACHED;
StructureFeature* StructureFeatures::SWAMP_HUT;
StructureFeature* StructureFeatures::STRONGHOLD;
StructureFeature* StructureFeatures::MONUMENT;
StructureFeature* StructureFeatures::OCEAN_RUIN_COLD;
StructureFeature* StructureFeatures::OCEAN_RUIN_WARM;
StructureFeature* StructureFeatures::FORTRESS;
StructureFeature* StructureFeatures::NETHER_FOSSIL;
StructureFeature* StructureFeatures::END_CITY;
StructureFeature* StructureFeatures::BURIED_TREASURE;
StructureFeature* StructureFeatures::BASTION_REMNANT;
StructureFeature* StructureFeatures::VILLAGE_PLAINS;
StructureFeature* StructureFeatures::VILLAGE_DESERT;
StructureFeature* StructureFeatures::VILLAGE_SAVANNA;
StructureFeature* StructureFeatures::VILLAGE_SNOWY;
StructureFeature* StructureFeatures::VILLAGE_TAIGA;
StructureFeature* StructureFeatures::RUINED_PORTAL;
StructureFeature* StructureFeatures::RUINED_PORTAL_DESERT;
StructureFeature* StructureFeatures::RUINED_PORTAL_JUNGLE;
StructureFeature* StructureFeatures::RUINED_PORTAL_SWAMP;
StructureFeature* StructureFeatures::RUINED_PORTAL_MOUNTAIN;
StructureFeature* StructureFeatures::RUINED_PORTAL_OCEAN;
StructureFeature* StructureFeatures::RUINED_PORTAL_NETHER;

static StructureFeature* registerStructure(std::string name, StructureFeature* feature) {
    StructureFeatures::registry.emplace(std::move(name), feature);
    return feature;
}

void StructureFeatures::configureStructures() {
//    PILLAGER_OUTPOST = registerStructure("pillager_outpost", Structures::PILLAGER_OUTPOST->withConfiguration(new VillageConfig(() -> {
//        return PillagerOutpostPools.field_244088_a;
//    }, 7)));
    MINESHAFT = registerStructure("mineshaft", Structures::MINESHAFT->withConfiguration(MineshaftConfig{0.004F, MineshaftType::NORMAL}));
    MINESHAFT_BADLANDS = registerStructure("mineshaft_mesa", Structures::MINESHAFT->withConfiguration(MineshaftConfig{0.004F, MineshaftType::MESA}));
//    MANSION = registerStructure("mansion", Structures::WOODLAND_MANSION->withConfiguration(NoFeatureConfig.field_236559_b_));
//    JUNGLE_PYRAMID = registerStructure("jungle_pyramid", Structures::JUNGLE_PYRAMID->withConfiguration(NoFeatureConfig.field_236559_b_));
//    DESERT_PYRAMID = registerStructure("desert_pyramid", Structures::DESERT_PYRAMID->withConfiguration(NoFeatureConfig.field_236559_b_));
//    IGLOO = registerStructure("igloo", Structures::IGLOO->withConfiguration(NoFeatureConfig.field_236559_b_));
//    SHIPWRECK = registerStructure("shipwreck", Structures::SHIPWRECK->withConfiguration(new ShipwreckConfig(false)));
//    SHIPWRECK_BEACHED = registerStructure("shipwreck_beached", Structures::SHIPWRECK->withConfiguration(new ShipwreckConfig(true)));
//    SWAMP_HUT = registerStructure("swamp_hut", Structures::SWAMP_HUT->withConfiguration(NoFeatureConfig.field_236559_b_));
//    STRONGHOLD = registerStructure("stronghold", Structures::STRONGHOLD->withConfiguration(NoFeatureConfig.field_236559_b_));
//    MONUMENT = registerStructure("monument", Structures::MONUMENT->withConfiguration(NoFeatureConfig.field_236559_b_));
//    OCEAN_RUIN_COLD = registerStructure("ocean_ruin_cold", Structures::OCEAN_RUIN->withConfiguration(new OceanRuinConfig(OceanRuinStructures::Type.COLD, 0.3F, 0.9F)));
//    OCEAN_RUIN_WARM = registerStructure("ocean_ruin_warm", Structures::OCEAN_RUIN->withConfiguration(new OceanRuinConfig(OceanRuinStructures::Type.WARM, 0.3F, 0.9F)));
//    FORTRESS = registerStructure("fortress", Structures::FORTRESS->withConfiguration(NoFeatureConfig.field_236559_b_));
//    NETHER_FOSSIL = registerStructure("nether_fossil", Structures::NETHER_FOSSIL->withConfiguration(NoFeatureConfig.field_236559_b_));
//    END_CITY = registerStructure("end_city", Structures::END_CITY->withConfiguration(NoFeatureConfig.field_236559_b_));
//    BURIED_TREASURE = registerStructure("buried_treasure", Structures::BURIED_TREASURE->withConfiguration(new ProbabilityConfig(0.01F)));
//    BASTION_REMNANT = registerStructure("bastion_remnant", Structures::BASTION_REMNANT->withConfiguration(new VillageConfig(() -> {
//        return BastionRemnantsPieces.field_243686_a;
//    }, 6)));
//    VILLAGE_PLAINS = registerStructure("village_plains", Structures::VILLAGE->withConfiguration(new VillageConfig(() -> {
//        return PlainsVillagePools.field_244090_a;
//    }, 6)));
//    VILLAGE_DESERT = registerStructure("village_desert", Structures::VILLAGE->withConfiguration(new VillageConfig(() -> {
//        return DesertVillagePools.field_243774_a;
//    }, 6)));
//    VILLAGE_SAVANNA = registerStructure("village_savanna", Structures::VILLAGE->withConfiguration(new VillageConfig(() -> {
//        return SavannaVillagePools.field_244128_a;
//    }, 6)));
//    VILLAGE_SNOWY = registerStructure("village_snowy", Structures::VILLAGE->withConfiguration(new VillageConfig(() -> {
//        return SnowyVillagePools.field_244129_a;
//    }, 6)));
//    VILLAGE_TAIGA = registerStructure("village_taiga", Structures::VILLAGE->withConfiguration(new VillageConfig(() -> {
//        return TaigaVillagePools.field_244193_a;
//    }, 6)));
//    RUINED_PORTAL = registerStructure("ruined_portal", Structures::RUINED_PORTAL->withConfiguration(new RuinedPortalFeatureConfig(RuinedPortalStructures::Location.STANDARD)));
//    RUINED_PORTAL_DESERT = registerStructure("ruined_portal_desert", Structures::RUINED_PORTAL->withConfiguration(new RuinedPortalFeatureConfig(RuinedPortalStructures::Location.DESERT)));
//    RUINED_PORTAL_JUNGLE = registerStructure("ruined_portal_jungle", Structures::RUINED_PORTAL->withConfiguration(new RuinedPortalFeatureConfig(RuinedPortalStructures::Location.JUNGLE)));
//    RUINED_PORTAL_SWAMP = registerStructure("ruined_portal_swamp", Structures::RUINED_PORTAL->withConfiguration(new RuinedPortalFeatureConfig(RuinedPortalStructures::Location.SWAMP)));
//    RUINED_PORTAL_MOUNTAIN = registerStructure("ruined_portal_mountain", Structures::RUINED_PORTAL->withConfiguration(new RuinedPortalFeatureConfig(RuinedPortalStructures::Location.MOUNTAIN)));
//    RUINED_PORTAL_OCEAN = registerStructure("ruined_portal_ocean", Structures::RUINED_PORTAL->withConfiguration(new RuinedPortalFeatureConfig(RuinedPortalStructures::Location.OCEAN)));
//    RUINED_PORTAL_NETHER = registerStructure("ruined_portal_nether", Structures::RUINED_PORTAL->withConfiguration(new RuinedPortalFeatureConfig(RuinedPortalStructures::Location.NETHER)));
}
