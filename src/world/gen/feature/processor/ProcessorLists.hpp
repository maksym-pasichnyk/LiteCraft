#pragma once

struct StructureProcessorList;
struct ProcessorLists {
    //private static final ProcessorRule ADD_GILDED_BLACKSTONE = new ProcessorRule(new RandomBlockMatchTest(Blocks.BLACKSTONE, 0.01f), AlwaysTrueTest.INSTANCE, Blocks.GILDED_BLACKSTONE.defaultBlockState());
    //private static final ProcessorRule REMOVE_GILDED_BLACKSTONE = new ProcessorRule(new RandomBlockMatchTest(Blocks.GILDED_BLACKSTONE, 0.5f), AlwaysTrueTest.INSTANCE, Blocks.BLACKSTONE.defaultBlockState());
    static StructureProcessorList* EMPTY;
    static StructureProcessorList* ZOMBIE_PLAINS;
    static StructureProcessorList* ZOMBIE_SAVANNA;
    static StructureProcessorList* ZOMBIE_SNOWY;
    static StructureProcessorList* ZOMBIE_TAIGA;
    static StructureProcessorList* ZOMBIE_DESERT;
    static StructureProcessorList* MOSSIFY_10_PERCENT;
    static StructureProcessorList* MOSSIFY_20_PERCENT;
    static StructureProcessorList* MOSSIFY_70_PERCENT;
    static StructureProcessorList* STREET_PLAINS;
    static StructureProcessorList* STREET_SAVANNA;
    static StructureProcessorList* STREET_SNOWY_OR_TAIGA;
    static StructureProcessorList* FARM_PLAINS;
    static StructureProcessorList* FARM_SAVANNA;
    static StructureProcessorList* FARM_SNOWY;
    static StructureProcessorList* FARM_TAIGA;
    static StructureProcessorList* FARM_DESERT;
    static StructureProcessorList* OUTPOST_ROT;
    static StructureProcessorList* BOTTOM_RAMPART;
    static StructureProcessorList* TREASURE_ROOMS;
    static StructureProcessorList* HOUSING;
    static StructureProcessorList* SIDE_WALL_DEGRADATION;
    static StructureProcessorList* STABLE_DEGRADATION;
    static StructureProcessorList* BASTION_GENERIC_DEGRADATION;
    static StructureProcessorList* RAMPART_DEGRADATION;
    static StructureProcessorList* ENTRANCE_REPLACEMENT;
    static StructureProcessorList* BRIDGE;
    static StructureProcessorList* ROOF;
    static StructureProcessorList* HIGH_WALL;
    static StructureProcessorList* HIGH_RAMPART;
    static StructureProcessorList* FOSSIL_ROT;
    static StructureProcessorList* FOSSIL_COAL;
    static StructureProcessorList* FOSSIL_DIAMONDS;

    static void init();
};