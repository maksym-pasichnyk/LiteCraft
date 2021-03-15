#include "Biome.hpp"
#include "../chunk/Chunk.hpp"
#include "../gen/surface/ConfiguredSurfaceBuilders.hpp"

#include <nlohmann/json.hpp>

const PerlinNoiseGenerator Biome::TEMPERATURE_NOISE = PerlinNoiseGenerator(Random::from(1234), std::views::single(0));
const PerlinNoiseGenerator Biome::FROZEN_TEMPERATURE_NOISE = PerlinNoiseGenerator(Random::from(3456), std::views::iota(-2, 0 + 1));
const PerlinNoiseGenerator Biome::INFO_NOISE = PerlinNoiseGenerator(Random::from(2345), std::views::single(0));

std::map<int, std::unique_ptr<Biome>> Biome::biomes;
Biome* Biome::OCEAN{};
Biome* Biome::PLAINS{};
Biome* Biome::DESERT{};
Biome* Biome::MOUNTAINS{};
Biome* Biome::FOREST{};
Biome* Biome::TAIGA{};
Biome* Biome::SWAMP{};
Biome* Biome::RIVER{};
Biome* Biome::NETHER_WASTES{};
Biome* Biome::THE_END{};
Biome* Biome::FROZEN_OCEAN{};
Biome* Biome::FROZEN_RIVER{};
Biome* Biome::SNOWY_TUNDRA{};
Biome* Biome::SNOWY_MOUNTAINS{};
Biome* Biome::MUSHROOM_FIELDS{};
Biome* Biome::MUSHROOM_FIELD_SHORE{};
Biome* Biome::BEACH{};
Biome* Biome::DESERT_HILLS{};
Biome* Biome::WOODED_HILLS{};
Biome* Biome::TAIGA_HILLS{};
Biome* Biome::MOUNTAIN_EDGE{};
Biome* Biome::JUNGLE{};
Biome* Biome::JUNGLE_HILLS{};
Biome* Biome::JUNGLE_EDGE{};
Biome* Biome::DEEP_OCEAN{};
Biome* Biome::STONE_SHORE{};
Biome* Biome::SNOWY_BEACH{};
Biome* Biome::BIRCH_FOREST{};
Biome* Biome::BIRCH_FOREST_HILLS{};
Biome* Biome::DARK_FOREST{};
Biome* Biome::SNOWY_TAIGA{};
Biome* Biome::SNOWY_TAIGA_HILLS{};
Biome* Biome::GIANT_TREE_TAIGA{};
Biome* Biome::GIANT_TREE_TAIGA_HILLS{};
Biome* Biome::WOODED_MOUNTAINS{};
Biome* Biome::SAVANNA{};
Biome* Biome::SAVANNA_PLATEAU{};
Biome* Biome::BADLANDS{};
Biome* Biome::WOODED_BADLANDS_PLATEAU{};
Biome* Biome::BADLANDS_PLATEAU{};
Biome* Biome::SMALL_END_ISLANDS{};
Biome* Biome::END_MIDLANDS{};
Biome* Biome::END_HIGHLANDS{};
Biome* Biome::END_BARRENS{};
Biome* Biome::WARM_OCEAN{};
Biome* Biome::LUKEWARM_OCEAN{};
Biome* Biome::COLD_OCEAN{};
Biome* Biome::DEEP_WARM_OCEAN{};
Biome* Biome::DEEP_LUKEWARM_OCEAN{};
Biome* Biome::DEEP_COLD_OCEAN{};
Biome* Biome::DEEP_FROZEN_OCEAN{};
Biome* Biome::THE_VOID{};
Biome* Biome::SUNFLOWER_PLAINS{};
Biome* Biome::DESERT_LAKES{};
Biome* Biome::GRAVELLY_MOUNTAINS{};
Biome* Biome::FLOWER_FOREST{};
Biome* Biome::TAIGA_MOUNTAINS{};
Biome* Biome::SWAMP_HILLS{};
Biome* Biome::ICE_SPIKES{};
Biome* Biome::MODIFIED_JUNGLE{};
Biome* Biome::MODIFIED_JUNGLE_EDGE{};
Biome* Biome::TALL_BIRCH_FOREST{};
Biome* Biome::TALL_BIRCH_HILLS{};
Biome* Biome::DARK_FOREST_HILLS{};
Biome* Biome::SNOWY_TAIGA_MOUNTAINS{};
Biome* Biome::GIANT_SPRUCE_TAIGA{};
Biome* Biome::GIANT_SPRUCE_TAIGA_HILLS{};
Biome* Biome::MODIFIED_GRAVELLY_MOUNTAINS{};
Biome* Biome::SHATTERED_SAVANNA{};
Biome* Biome::SHATTERED_SAVANNA_PLATEAU{};
Biome* Biome::ERODED_BADLANDS{};
Biome* Biome::MODIFIED_WOODED_BADLANDS_PLATEAU{};
Biome* Biome::MODIFIED_BADLANDS_PLATEAU{};
Biome* Biome::BAMBOO_JUNGLE{};
Biome* Biome::BAMBOO_JUNGLE_HILLS{};
Biome* Biome::SOUL_SAND_VALLEY{};
Biome* Biome::CRIMSON_FOREST{};
Biome* Biome::WARPED_FOREST{};
Biome* Biome::BASALT_DELTAS{};
//std::map<std::string, int> BiomeDefinition::biomeIds {
//    { "ocean", 0 },
//    { "deep_ocean", 24 },
//    { "frozen_ocean", 10 },
//    { "deep_frozen_ocean", 50 },
//    { "cold_ocean", 46 },
//    { "deep_cold_ocean", 49 },
//    { "lukewarm_ocean", 45 },
//    { "deep_lukewarm_ocean", 48 },
//    { "warm_ocean", 44 },
//    { "deep_warm_ocean", 47 },
//    { "river", 7 },
//    { "frozen_river", 11 },
//    { "beach", 16 },
//    { "stone_shore", 25 },
//    { "snowy_beach", 26 },
//    { "forest", 4 },
//    { "wooded_hills", 18 },
//    { "flower_forest", 132 },
//    { "birch_forest", 27 },
//    { "birch_forest_hills", 28 },
//    { "tall_birch_forest", 155 },
//    { "tall_birch_hills", 156 },
//    { "dark_forest", 29 },
//    { "dark_forest_hills", 157 },
//    { "jungle", 21 },
//    { "jungle_hills", 22 },
//    { "modified_jungle", 149 },
//    { "jungle_edge", 23 },
//    { "modified_jungle_edge", 151 },
//    { "bamboo_jungle", 168 },
//    { "bamboo_jungle_hills", 169 },
//    { "taiga", 5 },
//    { "taiga_hills", 19 },
//    { "taiga_mountains", 133 },
//    { "snowy_taiga", 30 },
//    { "snowy_taiga_hills", 31 },
//    { "snowy_taiga_mountains", 158 },
//    { "giant_tree_taiga", 32 },
//    { "giant_tree_taiga_hills", 33 },
//    { "giant_spruce_taiga", 160 },
//    { "giant_spruce_taiga_hills", 161 },
//    { "mushroom_fields", 14 },
//    { "mushroom_field_shore", 15 },
//    { "swamp", 6 },
//    { "swamp_hills", 134 },
//    { "savanna", 35 },
//    { "savanna_plateau", 36 },
//    { "shattered_savanna", 163 },
//    { "shattered_savanna_plateau", 164 },
//    { "plains", 1 },
//    { "sunflower_plains", 129 },
//    { "desert", 2 },
//    { "desert_hills", 17 },
//    { "desert_lakes", 130 },
//    { "snowy_tundra", 12 },
//    { "snowy_mountains", 13 },
//    { "ice_spikes", 140 },
//    { "mountains", 3 },
//    { "wooded_mountains", 34 },
//    { "gravelly_mountains", 131 },
//    { "modified_gravelly_mountains", 162 },
//    { "mountain_edge", 20 },
//    { "badlands", 37 },
//    { "badlands_plateau", 39 },
//    { "modified_badlands_plateau", 167 },
//    { "wooded_badlands_plateau", 38 },
//    { "modified_wooded_badlands_plateau", 166 },
//    { "eroded_badlands", 165 },
//    { "dripstone_caves", 174 },
//    { "nether_wastes", 8 },
//    { "crimson_forest", 171 },
//    { "warped_forest", 172 },
//    { "soul_sand_valley", 170 },
//    { "basalt_deltas", 173 },
//    { "the_end", 9 },
//    { "small_end_islands", 40 },
//    { "end_midlands", 41 },
//    { "end_highlands", 42 },
//    { "end_barrens", 43 },
//    { "the_void", 127 }
//};

Biome* Biome::registerBiome(int id, Biome* biome) {
    biomes[id] = std::unique_ptr<Biome>(biome);
    return biome;
}

void withCavesAndCanyons(Biome* biome) {
    biome->carvers[0].emplace_back(ConfiguredCarver{
        .config = ProbabilityConfig {
            .probability = 0.14285715F
        },
        .carver = WorldCarver::CAVE.get()
    });
    biome->carvers[0].emplace_back(ConfiguredCarver{
        .config = ProbabilityConfig {
                .probability = 0.02F
        },
        .carver = WorldCarver::CAVE.get()
    });
}

void withOceanCavesAndCanyons(Biome* biome) {
    biome->carvers[0].emplace_back(ConfiguredCarver{
        .config = ProbabilityConfig {
            .probability = 0.06666667F
        },
        .carver = WorldCarver::CAVE.get()
    });
    biome->carvers[0].emplace_back(ConfiguredCarver{
        .config = ProbabilityConfig {
                .probability = 0.02F
        },
        .carver = WorldCarver::CAVE.get()
    });
}

Biome* makeOceanBiome() {
    auto biome = new Biome(-1.0, 0.1, ConfiguredSurfaceBuilders::OCEAN_SAND);
    withOceanCavesAndCanyons(biome);
    return biome;
}

Biome* makePlainsBiome() {
    auto biome = new Biome(0.125, 0.05, ConfiguredSurfaceBuilders::GRASS);
    withCavesAndCanyons(biome);
    return biome;
}

Biome* makeDesertBiome(float depth, float scale) {
    auto biome = new Biome(depth, scale, ConfiguredSurfaceBuilders::FULL_SAND);
    withCavesAndCanyons(biome);
    return biome;
}

Biome* makeMountainBiome(float depth, float scale) {
    auto biome = new Biome(depth, scale, ConfiguredSurfaceBuilders::MOUNTAIN);
    withCavesAndCanyons(biome);
    return biome;
}

Biome* makeForestBiome(float depth, float scale) {
    auto biome = new Biome(depth, scale, ConfiguredSurfaceBuilders::GRASS);
    withCavesAndCanyons(biome);
    return biome;
}

Biome* makeTaigaBiome(float depth, float scale) {
    auto biome = new Biome(depth, scale, ConfiguredSurfaceBuilders::GRASS);
    withCavesAndCanyons(biome);
    return biome;
}

Biome* makeSwampBiome(float depth, float scale) {
    auto biome = new Biome(depth, scale, ConfiguredSurfaceBuilders::SWAMP);
    withCavesAndCanyons(biome);
    return biome;
}

Biome* makeRiverBiome(float depth, float scale, float temperature) {
    auto biome = new Biome(depth, scale, ConfiguredSurfaceBuilders::GRASS);
    withCavesAndCanyons(biome);
    biome->temperature = temperature;
    return biome;
}

//void BiomeDefinition::loadMetaFile() {
//    using namespace std::string_view_literals;
//
//    for (const auto& e : std::filesystem::directory_iterator("../assets/definitions/biomes")) {
//        if (e.is_regular_file()) {
//            std::vector<char> bytes(std::filesystem::file_size(e.path()));
//            std::ifstream stream{e.path(), std::ios::binary};
//            stream.read(bytes.data(), bytes.size());
//            stream.close();
//
//            auto obj = nlohmann::json::parse(bytes, nullptr, true, true);
//            auto format = obj.erase(obj.find("format_version")).value();
//            auto& biome_info = obj.find("minecraft:biome").value();
//            auto& description = biome_info.find("description").value();
//            auto identifier = description.find("identifier").value().get<std::string>();
//
//            if (!biomeIds.contains(identifier)) {
//                fmt::print("can't find id for {} biome\n", identifier);
//            }
//
//            auto& components = biome_info.find("components").value();
//
//            SurfaceBuilder* builder{nullptr};
//
//            for (auto& [k, v] : components.items()) {
//                const auto split_pos = k.find_first_of(':');
//                if (split_pos != std::string::npos) {
//                    auto ns = std::string_view(k).substr(0, split_pos);
//                    auto component = std::string_view(k).substr(split_pos + 1);
//
//                    if (component == "climate"sv) {
//
//                    } else if (component == "overworld_height"sv) {
//
//                    } else if (component == "surface_parameters"sv) {
//
//                    } else if (component == "surface_material_adjustments"sv) {
//
//                    } else if (component == "swamp_surface"sv) {
//                        builder = ConfiguredSurfaceBuilders::SWAMP;
//                    } else if (component == "frozen_ocean_surface"sv) {
//                        builder = SurfaceBuilder::FrozenOcean.get();
//                    } else if (component == "mesa_surface"sv) {
//                        builder = ConfiguredSurfaceBuilders::BADLANDS;
//                    } else if (component == "nether_surface"sv) {
//                        builder = SurfaceBuilder::Nether.get();
//                    } else if (component == "the_end_surface"sv) {
//
//                    } else if (component == "overworld_generation_rules"sv) {
//
//                    } else if (component == "nether_generation_rules"sv) {
//
//                    }
//                } else {
//                    // this is biome_info tag
//                }
//            }
//        }
//    }
//}
//
//void BiomeDefinition::registerBiomes() {
//
//}

void Biome::registerBiomes() {
    OCEAN = registerBiome(0, makeOceanBiome());
    PLAINS = registerBiome(1, makePlainsBiome());
    DESERT = registerBiome(2, makeDesertBiome(0.125, 0.05));
    MOUNTAINS = registerBiome(3, makeMountainBiome(1.0, 0.5));
    FOREST = registerBiome(4, makeForestBiome(0.1, 0.2));
    TAIGA = registerBiome(5, makeTaigaBiome(0.2, 0.2));
    SWAMP = registerBiome(6, makeSwampBiome(-0.2, 0.1));
    RIVER = registerBiome(7, makeRiverBiome(-0.5, 0.0, 0.5));
    NETHER_WASTES = registerBiome(8, new Biome(0.1, 0.2, ConfiguredSurfaceBuilders::NETHER));
    THE_END = registerBiome(9, new Biome(0.1, 0.2, ConfiguredSurfaceBuilders::GRASS));
    FROZEN_OCEAN = registerBiome(10, new Biome(-1.0, 0.1, ConfiguredSurfaceBuilders::FROZEN_OCEAN));
    FROZEN_RIVER = registerBiome(11, new Biome(-0.5, 0.0, ConfiguredSurfaceBuilders::GRASS));
    SNOWY_TUNDRA = registerBiome(12, new Biome(0.125, 0.05, ConfiguredSurfaceBuilders::GRASS));
    SNOWY_MOUNTAINS = registerBiome(13, new Biome(0.45, 0.3, ConfiguredSurfaceBuilders::GRASS));
    MUSHROOM_FIELDS = registerBiome(14, new Biome(0.2, 0.3, ConfiguredSurfaceBuilders::GRASS));
    MUSHROOM_FIELD_SHORE = registerBiome(15, new Biome(0.0, 0.025, ConfiguredSurfaceBuilders::GRASS));
    BEACH = registerBiome(16, new Biome(0.0, 0.025, ConfiguredSurfaceBuilders::GRASS));
    DESERT_HILLS = registerBiome(17, new Biome(0.45, 0.3, ConfiguredSurfaceBuilders::GRASS));
    WOODED_HILLS = registerBiome(18, new Biome(0.45, 0.3, ConfiguredSurfaceBuilders::GRASS));
    TAIGA_HILLS = registerBiome(19, new Biome(0.45, 0.3, ConfiguredSurfaceBuilders::GRASS));
    MOUNTAIN_EDGE = registerBiome(20, new Biome(0.8, 0.3, ConfiguredSurfaceBuilders::GRASS));
    JUNGLE = registerBiome(21, new Biome(0.1, 0.2, ConfiguredSurfaceBuilders::GRASS));
    JUNGLE_HILLS = registerBiome(22, new Biome(0.45, 0.3, ConfiguredSurfaceBuilders::GRASS));
    JUNGLE_EDGE = registerBiome(23, new Biome(0.1, 0.2, ConfiguredSurfaceBuilders::GRASS));
    DEEP_OCEAN = registerBiome(24, new Biome(-1.8, 0.1, ConfiguredSurfaceBuilders::GRASS));
    STONE_SHORE = registerBiome(25, new Biome(0.1, 0.8, ConfiguredSurfaceBuilders::GRASS));
    SNOWY_BEACH = registerBiome(26, new Biome(0.0, 0.025, ConfiguredSurfaceBuilders::GRASS));
    BIRCH_FOREST = registerBiome(27, new Biome(0.1, 0.2, ConfiguredSurfaceBuilders::GRASS));
    BIRCH_FOREST_HILLS = registerBiome(28, new Biome(0.45, 0.3, ConfiguredSurfaceBuilders::GRASS));
    DARK_FOREST = registerBiome(29, new Biome(0.1, 0.2, ConfiguredSurfaceBuilders::GRASS));
    SNOWY_TAIGA = registerBiome(30, new Biome(0.2, 0.2, ConfiguredSurfaceBuilders::GRASS));
    SNOWY_TAIGA_HILLS = registerBiome(31, new Biome(0.45, 0.3, ConfiguredSurfaceBuilders::GRASS));
    GIANT_TREE_TAIGA = registerBiome(32, new Biome(0.2, 0.2, ConfiguredSurfaceBuilders::GIANT_TREE_TAIGA));
    GIANT_TREE_TAIGA_HILLS = registerBiome(33, new Biome(0.45, 0.3, ConfiguredSurfaceBuilders::GIANT_TREE_TAIGA));
    WOODED_MOUNTAINS = registerBiome(34, new Biome(1.0, 0.5, ConfiguredSurfaceBuilders::GRASS));
    SAVANNA = registerBiome(35, new Biome(0.125, 0.05, ConfiguredSurfaceBuilders::GRASS));
    SAVANNA_PLATEAU = registerBiome(36, new Biome(1.5, 0.025, ConfiguredSurfaceBuilders::GRASS));
    BADLANDS = registerBiome(37, new Biome(0.1, 0.2, ConfiguredSurfaceBuilders::BADLANDS));
    WOODED_BADLANDS_PLATEAU = registerBiome(38, new Biome(1.5, 0.025, ConfiguredSurfaceBuilders::WOODED_BADLANDS));
    BADLANDS_PLATEAU = registerBiome(39, new Biome(1.5, 0.025, ConfiguredSurfaceBuilders::BADLANDS));
    SMALL_END_ISLANDS = registerBiome(40, new Biome(0.1, 0.2, ConfiguredSurfaceBuilders::GRASS));
    END_MIDLANDS = registerBiome(41, new Biome(0.1, 0.2, ConfiguredSurfaceBuilders::GRASS));
    END_HIGHLANDS = registerBiome(42, new Biome(0.1, 0.2, ConfiguredSurfaceBuilders::GRASS));
    END_BARRENS = registerBiome(43, new Biome(0.1, 0.2, ConfiguredSurfaceBuilders::GRASS));
    WARM_OCEAN = registerBiome(44, new Biome(-1.0, 0.1, ConfiguredSurfaceBuilders::GRASS));
    LUKEWARM_OCEAN = registerBiome(45, new Biome(-1.0, 0.1, ConfiguredSurfaceBuilders::GRASS));
    COLD_OCEAN = registerBiome(46, new Biome(-1.0, 0.1, ConfiguredSurfaceBuilders::GRASS));
    DEEP_WARM_OCEAN = registerBiome(47, new Biome(-1.8, 0.1, ConfiguredSurfaceBuilders::GRASS));
    DEEP_LUKEWARM_OCEAN = registerBiome(48, new Biome(-1.8, 0.1, ConfiguredSurfaceBuilders::GRASS));
    DEEP_COLD_OCEAN = registerBiome(49, new Biome(-1.8, 0.1, ConfiguredSurfaceBuilders::GRASS));
    DEEP_FROZEN_OCEAN = registerBiome(50, new Biome(-1.8, 0.1, ConfiguredSurfaceBuilders::FROZEN_OCEAN));
    THE_VOID = registerBiome(127, new Biome(0.1, 0.2, ConfiguredSurfaceBuilders::NOPE));
    SUNFLOWER_PLAINS = registerBiome(129, new Biome(0.125, 0.05, ConfiguredSurfaceBuilders::GRASS));
    DESERT_LAKES = registerBiome(130, new Biome(0.225, 0.25, ConfiguredSurfaceBuilders::GRASS));
    GRAVELLY_MOUNTAINS = registerBiome(131, new Biome(1.0, 0.5, ConfiguredSurfaceBuilders::GRAVELLY_MOUNTAIN));
    FLOWER_FOREST = registerBiome(132, new Biome(0.1, 0.4, ConfiguredSurfaceBuilders::GRASS));
    TAIGA_MOUNTAINS = registerBiome(133, new Biome(0.3, 0.4, ConfiguredSurfaceBuilders::GRASS));
    SWAMP_HILLS = registerBiome(134, new Biome(-0.1, 0.3, ConfiguredSurfaceBuilders::SWAMP));
    ICE_SPIKES = registerBiome(140, new Biome(0.425, 0.45000002, ConfiguredSurfaceBuilders::GRASS));
    MODIFIED_JUNGLE = registerBiome(149, new Biome(0.2, 0.4, ConfiguredSurfaceBuilders::GRASS));
    MODIFIED_JUNGLE_EDGE = registerBiome(151, new Biome(0.2, 0.4, ConfiguredSurfaceBuilders::GRASS));
    TALL_BIRCH_FOREST = registerBiome(155, new Biome(0.2, 0.4, ConfiguredSurfaceBuilders::GRASS));
    TALL_BIRCH_HILLS = registerBiome(156, new Biome(0.55, 0.5, ConfiguredSurfaceBuilders::GRASS));
    DARK_FOREST_HILLS = registerBiome(157, new Biome(0.2, 0.4, ConfiguredSurfaceBuilders::GRASS));
    SNOWY_TAIGA_MOUNTAINS = registerBiome(158, new Biome(0.3, 0.4, ConfiguredSurfaceBuilders::GRASS));
    GIANT_SPRUCE_TAIGA = registerBiome(160, new Biome(0.2, 0.2, ConfiguredSurfaceBuilders::GIANT_TREE_TAIGA));
    GIANT_SPRUCE_TAIGA_HILLS = registerBiome(161, new Biome(0.2, 0.2, ConfiguredSurfaceBuilders::GIANT_TREE_TAIGA));
    MODIFIED_GRAVELLY_MOUNTAINS = registerBiome(162, new Biome(1.0, 0.5, ConfiguredSurfaceBuilders::GRAVELLY_MOUNTAIN));
    SHATTERED_SAVANNA = registerBiome(163, new Biome(0.3625, 1.225, ConfiguredSurfaceBuilders::SHATTERED_SAVANNA));
    SHATTERED_SAVANNA_PLATEAU = registerBiome(164, new Biome(1.05, 1.2125001, ConfiguredSurfaceBuilders::SHATTERED_SAVANNA));
    ERODED_BADLANDS = registerBiome(165, new Biome(0.1, 0.2, ConfiguredSurfaceBuilders::ERODED_BADLANDS));
    MODIFIED_WOODED_BADLANDS_PLATEAU = registerBiome(166, new Biome(0.45, 0.3, ConfiguredSurfaceBuilders::WOODED_BADLANDS));
    MODIFIED_BADLANDS_PLATEAU = registerBiome(167, new Biome(0.45, 0.3, ConfiguredSurfaceBuilders::BADLANDS));
    BAMBOO_JUNGLE = registerBiome(168, new Biome(0.1, 0.2, ConfiguredSurfaceBuilders::GRASS));
    BAMBOO_JUNGLE_HILLS = registerBiome(169, new Biome(0.45, 0.3, ConfiguredSurfaceBuilders::GRASS));
    SOUL_SAND_VALLEY = registerBiome(170, new Biome(0.1, 0.2, ConfiguredSurfaceBuilders::SOUL_SAND_VALLEY));
    CRIMSON_FOREST = registerBiome(171, new Biome(0.1, 0.2, ConfiguredSurfaceBuilders::CRIMSON_FOREST));
    WARPED_FOREST = registerBiome(172, new Biome(0.1, 0.2, ConfiguredSurfaceBuilders::WARPED_FOREST));
    BASALT_DELTAS = registerBiome(173, new Biome(0.1, 0.2, ConfiguredSurfaceBuilders::BASALT_DELTAS));
}