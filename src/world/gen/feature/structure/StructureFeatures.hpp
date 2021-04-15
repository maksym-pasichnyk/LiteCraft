#pragma once

#include "StructureFeature.hpp"

#include <memory>
#include <string>
#include <map>

struct StructureFeatures {
    static std::map<std::string, std::unique_ptr<StructureFeature>> registry;

    static StructureFeature* PILLAGER_OUTPOST;
    static StructureFeature* MINESHAFT;
    static StructureFeature* MINESHAFT_BADLANDS;
    static StructureFeature* MANSION;
    static StructureFeature* JUNGLE_PYRAMID;
    static StructureFeature* DESERT_PYRAMID;
    static StructureFeature* IGLOO;
    static StructureFeature* SHIPWRECK;
    static StructureFeature* SHIPWRECK_BEACHED;
    static StructureFeature* SWAMP_HUT;
    static StructureFeature* STRONGHOLD;
    static StructureFeature* MONUMENT;
    static StructureFeature* OCEAN_RUIN_COLD;
    static StructureFeature* OCEAN_RUIN_WARM;
    static StructureFeature* FORTRESS;
    static StructureFeature* NETHER_FOSSIL;
    static StructureFeature* END_CITY;
    static StructureFeature* BURIED_TREASURE;
    static StructureFeature* BASTION_REMNANT;
    static StructureFeature* VILLAGE_PLAINS;
    static StructureFeature* VILLAGE_DESERT;
    static StructureFeature* VILLAGE_SAVANNA;
    static StructureFeature* VILLAGE_SNOWY;
    static StructureFeature* VILLAGE_TAIGA;
    static StructureFeature* RUINED_PORTAL;
    static StructureFeature* RUINED_PORTAL_DESERT;
    static StructureFeature* RUINED_PORTAL_JUNGLE;
    static StructureFeature* RUINED_PORTAL_SWAMP;
    static StructureFeature* RUINED_PORTAL_MOUNTAIN;
    static StructureFeature* RUINED_PORTAL_OCEAN;
    static StructureFeature* RUINED_PORTAL_NETHER;

    static void configureStructures();
};