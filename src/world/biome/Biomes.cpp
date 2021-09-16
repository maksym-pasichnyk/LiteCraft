#include "Biomes.hpp"
#include "Biome.hpp"

#include <configs.hpp>
#include <filesystem>
#include <fstream>

Registry<Biome> Biomes::biomes;

Biome* Biomes::OCEAN;
Biome* Biomes::PLAINS;
Biome* Biomes::DESERT;
Biome* Biomes::MOUNTAINS;
Biome* Biomes::FOREST;
Biome* Biomes::TAIGA;
Biome* Biomes::SWAMP;
Biome* Biomes::RIVER;
Biome* Biomes::NETHER_WASTES;
Biome* Biomes::THE_END;
Biome* Biomes::FROZEN_OCEAN;
Biome* Biomes::FROZEN_RIVER;
Biome* Biomes::SNOWY_TUNDRA;
Biome* Biomes::SNOWY_MOUNTAINS;
Biome* Biomes::MUSHROOM_FIELDS;
Biome* Biomes::MUSHROOM_FIELD_SHORE;
Biome* Biomes::BEACH;
Biome* Biomes::DESERT_HILLS;
Biome* Biomes::WOODED_HILLS;
Biome* Biomes::TAIGA_HILLS;
Biome* Biomes::MOUNTAIN_EDGE;
Biome* Biomes::JUNGLE;
Biome* Biomes::JUNGLE_HILLS;
Biome* Biomes::JUNGLE_EDGE;
Biome* Biomes::DEEP_OCEAN;
Biome* Biomes::STONE_SHORE;
Biome* Biomes::SNOWY_BEACH;
Biome* Biomes::BIRCH_FOREST;
Biome* Biomes::BIRCH_FOREST_HILLS;
Biome* Biomes::DARK_FOREST;
Biome* Biomes::SNOWY_TAIGA;
Biome* Biomes::SNOWY_TAIGA_HILLS;
Biome* Biomes::GIANT_TREE_TAIGA;
Biome* Biomes::GIANT_TREE_TAIGA_HILLS;
Biome* Biomes::WOODED_MOUNTAINS;
Biome* Biomes::SAVANNA;
Biome* Biomes::SAVANNA_PLATEAU;
Biome* Biomes::BADLANDS;
Biome* Biomes::WOODED_BADLANDS_PLATEAU;
Biome* Biomes::BADLANDS_PLATEAU;
Biome* Biomes::SMALL_END_ISLANDS;
Biome* Biomes::END_MIDLANDS;
Biome* Biomes::END_HIGHLANDS;
Biome* Biomes::END_BARRENS;
Biome* Biomes::WARM_OCEAN;
Biome* Biomes::LUKEWARM_OCEAN;
Biome* Biomes::COLD_OCEAN;
Biome* Biomes::DEEP_WARM_OCEAN;
Biome* Biomes::DEEP_LUKEWARM_OCEAN;
Biome* Biomes::DEEP_COLD_OCEAN;
Biome* Biomes::DEEP_FROZEN_OCEAN;
Biome* Biomes::THE_VOID;
Biome* Biomes::SUNFLOWER_PLAINS;
Biome* Biomes::DESERT_LAKES;
Biome* Biomes::GRAVELLY_MOUNTAINS;
Biome* Biomes::FLOWER_FOREST;
Biome* Biomes::TAIGA_MOUNTAINS;
Biome* Biomes::SWAMP_HILLS;
Biome* Biomes::ICE_SPIKES;
Biome* Biomes::MODIFIED_JUNGLE;
Biome* Biomes::MODIFIED_JUNGLE_EDGE;
Biome* Biomes::TALL_BIRCH_FOREST;
Biome* Biomes::TALL_BIRCH_HILLS;
Biome* Biomes::DARK_FOREST_HILLS;
Biome* Biomes::SNOWY_TAIGA_MOUNTAINS;
Biome* Biomes::GIANT_SPRUCE_TAIGA;
Biome* Biomes::GIANT_SPRUCE_TAIGA_HILLS;
Biome* Biomes::MODIFIED_GRAVELLY_MOUNTAINS;
Biome* Biomes::SHATTERED_SAVANNA;
Biome* Biomes::SHATTERED_SAVANNA_PLATEAU;
Biome* Biomes::ERODED_BADLANDS;
Biome* Biomes::MODIFIED_WOODED_BADLANDS_PLATEAU;
Biome* Biomes::MODIFIED_BADLANDS_PLATEAU;
Biome* Biomes::BAMBOO_JUNGLE;
Biome* Biomes::BAMBOO_JUNGLE_HILLS;
Biome* Biomes::SOUL_SAND_VALLEY;
Biome* Biomes::CRIMSON_FOREST;
Biome* Biomes::WARPED_FOREST;
Biome* Biomes::BASALT_DELTAS;

static auto loadFromResources(int id, std::string name) -> Biome* {
    std::ifstream in{fmt::format("definitions/biomes/{}.json", name), std::ios::binary};

    auto obj = Json::Read::read(in).value();
    auto&& o = obj.to_object();

    return Biomes::biomes.add(id, std::move(name), std::make_unique<Biome>(Biome{
        .climate {
           .precipitation = o.at("precipitation"),
           .temperature = o.at("temperature"),
           .temperatureModifier = o.at("temperature_modifier"),
           .downfall = o.at("downfall")
        },
        .biomeGenerationSettings{
           .surfaceBuilder = o.at("surface_builder"),
           .carvers = o.at("carvers"),
           .features = o.at("features"),
           .structures = o.at("structures")
        },
        .mobSpawnInfo{
           .creatureSpawnProbability = o.at("creature_spawn_probability"),
           .spawners = o.at("spawners"),
           .spawnCosts = o.at("spawn_costs"),
           .playerSpawnFriendly = o.at("player_spawn_friendly"),
        },
        .depth = o.at("depth"),
        .scale = o.at("scale"),
        .category = o.at("category"),
        .effects = o.at("effects")
    }));
}

void Biomes::init() {
    using namespace std::string_literals;

    OCEAN = loadFromResources(0, "ocean");
    PLAINS = loadFromResources(1, "plains");
    DESERT = loadFromResources(2, "desert");
    MOUNTAINS = loadFromResources(3, "mountains");
    FOREST = loadFromResources(4, "forest");
    TAIGA = loadFromResources(5, "taiga");
    SWAMP = loadFromResources(6, "swamp");
    RIVER = loadFromResources(7, "river");
    NETHER_WASTES = loadFromResources(8, "nether_wastes");
    THE_END = loadFromResources(9, "the_end");
    FROZEN_OCEAN = loadFromResources(10, "frozen_ocean");
    FROZEN_RIVER = loadFromResources(11, "frozen_river");
    SNOWY_TUNDRA = loadFromResources(12, "snowy_tundra");
    SNOWY_MOUNTAINS = loadFromResources(13, "snowy_mountains");
    MUSHROOM_FIELDS = loadFromResources(14, "mushroom_fields");
    MUSHROOM_FIELD_SHORE = loadFromResources(15, "mushroom_field_shore");
    BEACH = loadFromResources(16, "beach");
    DESERT_HILLS = loadFromResources(17, "desert_hills");
    WOODED_HILLS = loadFromResources(18, "wooded_hills");
    TAIGA_HILLS = loadFromResources(19, "taiga_hills");
    MOUNTAIN_EDGE = loadFromResources(20, "mountain_edge");
    JUNGLE = loadFromResources(21, "jungle");
    JUNGLE_HILLS = loadFromResources(22, "jungle_hills");
    JUNGLE_EDGE = loadFromResources(23, "jungle_edge");
    DEEP_OCEAN = loadFromResources(24, "deep_ocean");
    STONE_SHORE = loadFromResources(25, "stone_shore");
    SNOWY_BEACH = loadFromResources(26, "snowy_beach");
    BIRCH_FOREST = loadFromResources(27, "birch_forest");
    BIRCH_FOREST_HILLS = loadFromResources(28, "birch_forest_hills");
    DARK_FOREST = loadFromResources(29, "dark_forest");
    SNOWY_TAIGA = loadFromResources(30, "snowy_taiga");
    SNOWY_TAIGA_HILLS = loadFromResources(31, "snowy_taiga_hills");
    GIANT_TREE_TAIGA = loadFromResources(32, "giant_tree_taiga");
    GIANT_TREE_TAIGA_HILLS = loadFromResources(33, "giant_tree_taiga_hills");
    WOODED_MOUNTAINS = loadFromResources(34, "wooded_mountains");
    SAVANNA = loadFromResources(35, "savanna");
    SAVANNA_PLATEAU = loadFromResources(36, "savanna_plateau");
    BADLANDS = loadFromResources(37, "badlands");
    WOODED_BADLANDS_PLATEAU = loadFromResources(38, "wooded_badlands_plateau");
    BADLANDS_PLATEAU = loadFromResources(39, "badlands_plateau");
    SMALL_END_ISLANDS = loadFromResources(40, "small_end_islands");
    END_MIDLANDS = loadFromResources(41, "end_midlands");
    END_HIGHLANDS = loadFromResources(42, "end_highlands");
    END_BARRENS = loadFromResources(43, "end_barrens");
    WARM_OCEAN = loadFromResources(44, "warm_ocean");
    LUKEWARM_OCEAN = loadFromResources(45, "lukewarm_ocean");
    COLD_OCEAN = loadFromResources(46, "cold_ocean");
    DEEP_WARM_OCEAN = loadFromResources(47, "deep_warm_ocean");
    DEEP_LUKEWARM_OCEAN = loadFromResources(48, "deep_lukewarm_ocean");
    DEEP_COLD_OCEAN = loadFromResources(49, "deep_cold_ocean");
    DEEP_FROZEN_OCEAN = loadFromResources(50, "deep_frozen_ocean");
    THE_VOID = loadFromResources(127, "the_void");
    SUNFLOWER_PLAINS = loadFromResources(129, "sunflower_plains");
    DESERT_LAKES = loadFromResources(130, "desert_lakes");
    GRAVELLY_MOUNTAINS = loadFromResources(131, "gravelly_mountains");
    FLOWER_FOREST = loadFromResources(132, "flower_forest");
    TAIGA_MOUNTAINS = loadFromResources(133, "taiga_mountains");
    SWAMP_HILLS = loadFromResources(134, "swamp_hills");
    ICE_SPIKES = loadFromResources(140, "ice_spikes");
    MODIFIED_JUNGLE = loadFromResources(149, "modified_jungle");
    MODIFIED_JUNGLE_EDGE = loadFromResources(151, "modified_jungle_edge");
    TALL_BIRCH_FOREST = loadFromResources(155, "tall_birch_forest");
    TALL_BIRCH_HILLS = loadFromResources(156, "tall_birch_hills");
    DARK_FOREST_HILLS = loadFromResources(157, "dark_forest_hills");
    SNOWY_TAIGA_MOUNTAINS = loadFromResources(158, "snowy_taiga_mountains");
    GIANT_SPRUCE_TAIGA = loadFromResources(160, "giant_spruce_taiga");
    GIANT_SPRUCE_TAIGA_HILLS = loadFromResources(161, "giant_spruce_taiga_hills");
    MODIFIED_GRAVELLY_MOUNTAINS = loadFromResources(162, "modified_gravelly_mountains");
    SHATTERED_SAVANNA = loadFromResources(163, "shattered_savanna");
    SHATTERED_SAVANNA_PLATEAU = loadFromResources(164, "shattered_savanna_plateau");
    ERODED_BADLANDS = loadFromResources(165, "eroded_badlands");
    MODIFIED_WOODED_BADLANDS_PLATEAU = loadFromResources(166, "modified_wooded_badlands_plateau");
    MODIFIED_BADLANDS_PLATEAU = loadFromResources(167, "modified_badlands_plateau");
    BAMBOO_JUNGLE = loadFromResources(168, "bamboo_jungle");
    BAMBOO_JUNGLE_HILLS = loadFromResources(169, "bamboo_jungle_hills");
    SOUL_SAND_VALLEY = loadFromResources(170, "soul_sand_valley");
    CRIMSON_FOREST = loadFromResources(171, "crimson_forest");
    WARPED_FOREST = loadFromResources(172, "warped_forest");
    BASALT_DELTAS = loadFromResources(173, "basalt_deltas");

//    for (const auto& [name, biome] : Biomes::biomes.objects) {
//        std::ofstream out{fmt::format("definitions/biomes/{}.json", name), std::ios::binary};
//        out << Json{
//            {"depth", biome->depth},
//            {"scale", biome->scale},
//            {"precipitation", biome->climate.precipitation},
//            {"category", biome->category},
//            {"temperature", biome->climate.temperature},
//            {"temperature_modifier", biome->climate.temperatureModifier},
//            {"downfall", biome->climate.downfall},
//            {"player_spawn_friendly", biome->mobSpawnInfo.playerSpawnFriendly},
//            {"creature_spawn_probability", biome->mobSpawnInfo.creatureSpawnProbability},
//            {"effects", biome->effects},
//            {"surface_builder", biome->biomeGenerationSettings.surfaceBuilder},
//            {"carvers", biome->biomeGenerationSettings.carvers},
//            {"features", biome->biomeGenerationSettings.features},
//            {"structures", biome->biomeGenerationSettings.structures},
//            {"spawners", biome->mobSpawnInfo.spawners},
//            {"spawn_costs", biome->mobSpawnInfo.spawnCosts}
//        };
//    }
}