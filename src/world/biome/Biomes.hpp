#pragma once

#include <map>
#include <memory>
#include <util/Registry.hpp>

struct Biome;
struct ResourceManager;

struct Biomes {
    static Registry<Biome> biomes;

//    static Biome* OCEAN;
//    static Biome* PLAINS;
//    static Biome* DESERT;
//    static Biome* MOUNTAINS;
//    static Biome* FOREST;
//    static Biome* TAIGA;
//    static Biome* SWAMP;
//    static Biome* RIVER;
//    static Biome* NETHER_WASTES;
//    static Biome* THE_END;
//    static Biome* FROZEN_OCEAN;
//    static Biome* FROZEN_RIVER;
//    static Biome* SNOWY_TUNDRA;
//    static Biome* SNOWY_MOUNTAINS;
//    static Biome* MUSHROOM_FIELDS;
//    static Biome* MUSHROOM_FIELD_SHORE;
//    static Biome* BEACH;
//    static Biome* DESERT_HILLS;
//    static Biome* WOODED_HILLS;
//    static Biome* TAIGA_HILLS;
//    static Biome* MOUNTAIN_EDGE;
//    static Biome* JUNGLE;
//    static Biome* JUNGLE_HILLS;
//    static Biome* JUNGLE_EDGE;
//    static Biome* DEEP_OCEAN;
//    static Biome* STONE_SHORE;
//    static Biome* SNOWY_BEACH;
//    static Biome* BIRCH_FOREST;
//    static Biome* BIRCH_FOREST_HILLS;
//    static Biome* DARK_FOREST;
//    static Biome* SNOWY_TAIGA;
//    static Biome* SNOWY_TAIGA_HILLS;
//    static Biome* GIANT_TREE_TAIGA;
//    static Biome* GIANT_TREE_TAIGA_HILLS;
//    static Biome* WOODED_MOUNTAINS;
//    static Biome* SAVANNA;
//    static Biome* SAVANNA_PLATEAU;
//    static Biome* BADLANDS;
//    static Biome* WOODED_BADLANDS_PLATEAU;
//    static Biome* BADLANDS_PLATEAU;
//    static Biome* SMALL_END_ISLANDS;
//    static Biome* END_MIDLANDS;
//    static Biome* END_HIGHLANDS;
//    static Biome* END_BARRENS;
//    static Biome* WARM_OCEAN;
//    static Biome* LUKEWARM_OCEAN;
//    static Biome* COLD_OCEAN;
//    static Biome* DEEP_WARM_OCEAN;
//    static Biome* DEEP_LUKEWARM_OCEAN;
//    static Biome* DEEP_COLD_OCEAN;
//    static Biome* DEEP_FROZEN_OCEAN;
//    static Biome* THE_VOID;
//    static Biome* SUNFLOWER_PLAINS;
//    static Biome* DESERT_LAKES;
//    static Biome* GRAVELLY_MOUNTAINS;
//    static Biome* FLOWER_FOREST;
//    static Biome* TAIGA_MOUNTAINS;
//    static Biome* SWAMP_HILLS;
//    static Biome* ICE_SPIKES;
//    static Biome* MODIFIED_JUNGLE;
//    static Biome* MODIFIED_JUNGLE_EDGE;
//    static Biome* TALL_BIRCH_FOREST;
//    static Biome* TALL_BIRCH_HILLS;
//    static Biome* DARK_FOREST_HILLS;
//    static Biome* SNOWY_TAIGA_MOUNTAINS;
//    static Biome* GIANT_SPRUCE_TAIGA;
//    static Biome* GIANT_SPRUCE_TAIGA_HILLS;
//    static Biome* MODIFIED_GRAVELLY_MOUNTAINS;
//    static Biome* SHATTERED_SAVANNA;
//    static Biome* SHATTERED_SAVANNA_PLATEAU;
//    static Biome* ERODED_BADLANDS;
//    static Biome* MODIFIED_WOODED_BADLANDS_PLATEAU;
//    static Biome* MODIFIED_BADLANDS_PLATEAU;
//    static Biome* BAMBOO_JUNGLE;
//    static Biome* BAMBOO_JUNGLE_HILLS;
//    static Biome* SOUL_SAND_VALLEY;
//    static Biome* CRIMSON_FOREST;
//    static Biome* WARPED_FOREST;
//    static Biome* BASALT_DELTAS;

    static auto findByName(const std::string& name) -> Biome* {
        return biomes.get(name).value_or(nullptr);
    }

    static void init(ResourceManager& resources);
};
