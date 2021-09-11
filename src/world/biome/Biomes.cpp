#include "Biomes.hpp"
#include "Biome.hpp"

#include "BiomeMaker.hpp"

#include <fstream>
#include <configs.hpp>

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

static auto registerBiome(int id, std::string name, Biome* biome) -> Biome* {
    return Biomes::biomes.add(id, std::move(name), std::unique_ptr<Biome>(biome));
}

template<>
struct Json::Serialize<EntityType> {
    static auto to_json(const EntityType& type) -> Json {
        using namespace std::string_literals;

        switch (type) {
            case EntityType::AREA_EFFECT_CLOUD: return "area_effect_cloud"s;
            case EntityType::ARMOR_STAND: return "armor_stand"s;
            case EntityType::ARROW: return "arrow"s;
            case EntityType::BAT: return "bat"s;
            case EntityType::BEE: return "bee"s;
            case EntityType::BLAZE: return "blaze"s;
            case EntityType::BOAT: return "boat"s;
            case EntityType::CAT: return "cat"s;
            case EntityType::CAVE_SPIDER: return "cave_spider"s;
            case EntityType::CHICKEN: return "chicken"s;
            case EntityType::COD: return "cod"s;
            case EntityType::COW: return "cow"s;
            case EntityType::CREEPER: return "creeper"s;
            case EntityType::DOLPHIN: return "dolphin"s;
            case EntityType::DONKEY: return "donkey"s;
            case EntityType::DRAGON_FIREBALL: return "dragon_fireball"s;
            case EntityType::DROWNED: return "drowned"s;
            case EntityType::ELDER_GUARDIAN: return "elder_guardian"s;
            case EntityType::END_CRYSTAL: return "end_crystal"s;
            case EntityType::ENDER_DRAGON: return "ender_dragon"s;
            case EntityType::ENDERMAN: return "enderman"s;
            case EntityType::ENDERMITE: return "endermite"s;
            case EntityType::EVOKER: return "evoker"s;
            case EntityType::EVOKER_FANGS: return "evoker_fangs"s;
            case EntityType::EXPERIENCE_ORB: return "experience_orb"s;
            case EntityType::EYE_OF_ENDER: return "eye_of_ender"s;
            case EntityType::FALLING_BLOCK: return "falling_block"s;
            case EntityType::FIREWORK_ROCKET: return "firework_rocket"s;
            case EntityType::FOX: return "fox"s;
            case EntityType::GHAST: return "ghast"s;
            case EntityType::GIANT: return "giant"s;
            case EntityType::GUARDIAN: return "guardian"s;
            case EntityType::HOGLIN: return "hoglin"s;
            case EntityType::HORSE: return "horse"s;
            case EntityType::HUSK: return "husk"s;
            case EntityType::ILLUSIONER: return "illusioner"s;
            case EntityType::IRON_GOLEM: return "iron_golem"s;
            case EntityType::ITEM: return "item"s;
            case EntityType::ITEM_FRAME: return "item_frame"s;
            case EntityType::FIREBALL: return "fireball"s;
            case EntityType::LEASH_KNOT: return "leash_knot"s;
            case EntityType::LIGHTNING_BOLT: return "lightning_bolt"s;
            case EntityType::LLAMA: return "llama"s;
            case EntityType::LLAMA_SPIT: return "llama_spit"s;
            case EntityType::MAGMA_CUBE: return "magma_cube"s;
            case EntityType::MINECART: return "minecart"s;
            case EntityType::CHEST_MINECART: return "chest_minecart"s;
            case EntityType::COMMAND_BLOCK_MINECART: return "command_block_minecart"s;
            case EntityType::FURNACE_MINECART: return "furnace_minecart"s;
            case EntityType::HOPPER_MINECART: return "hopper_minecart"s;
            case EntityType::SPAWNER_MINECART: return "spawner_minecart"s;
            case EntityType::TNT_MINECART: return "tnt_minecart"s;
            case EntityType::MULE: return "mule"s;
            case EntityType::MOOSHROOM: return "mooshroom"s;
            case EntityType::OCELOT: return "ocelot"s;
            case EntityType::PAINTING: return "painting"s;
            case EntityType::PANDA: return "panda"s;
            case EntityType::PARROT: return "parrot"s;
            case EntityType::PHANTOM: return "phantom"s;
            case EntityType::PIG: return "pig"s;
            case EntityType::PIGLIN: return "piglin"s;
            case EntityType::field_242287_aj: return "field_242287_aj"s;
            case EntityType::PILLAGER: return "pillager"s;
            case EntityType::POLAR_BEAR: return "polar_bear"s;
            case EntityType::TNT: return "tnt"s;
            case EntityType::PUFFERFISH: return "pufferfish"s;
            case EntityType::RABBIT: return "rabbit"s;
            case EntityType::RAVAGER: return "ravager"s;
            case EntityType::SALMON: return "salmon"s;
            case EntityType::SHEEP: return "sheep"s;
            case EntityType::SHULKER: return "shulker"s;
            case EntityType::SHULKER_BULLET: return "shulker_bullet"s;
            case EntityType::SILVERFISH: return "silverfish"s;
            case EntityType::SKELETON: return "skeleton"s;
            case EntityType::SKELETON_HORSE: return "skeleton_horse"s;
            case EntityType::SLIME: return "slime"s;
            case EntityType::SMALL_FIREBALL: return "small_fireball"s;
            case EntityType::SNOW_GOLEM: return "snow_golem"s;
            case EntityType::SNOWBALL: return "snowball"s;
            case EntityType::SPECTRAL_ARROW: return "spectral_arrow"s;
            case EntityType::SPIDER: return "spider"s;
            case EntityType::SQUID: return "squid"s;
            case EntityType::STRAY: return "stray"s;
            case EntityType::STRIDER: return "strider"s;
            case EntityType::EGG: return "egg"s;
            case EntityType::ENDER_PEARL: return "ender_pearl"s;
            case EntityType::EXPERIENCE_BOTTLE: return "experience_bottle"s;
            case EntityType::POTION: return "potion"s;
            case EntityType::TRIDENT: return "trident"s;
            case EntityType::TRADER_LLAMA: return "trader_llama"s;
            case EntityType::TROPICAL_FISH: return "tropical_fish"s;
            case EntityType::TURTLE: return "turtle"s;
            case EntityType::VEX: return "vex"s;
            case EntityType::VILLAGER: return "villager"s;
            case EntityType::VINDICATOR: return "vindicator"s;
            case EntityType::WANDERING_TRADER: return "wandering_trader"s;
            case EntityType::WITCH: return "witch"s;
            case EntityType::WITHER: return "wither"s;
            case EntityType::WITHER_SKELETON: return "wither_skeleton"s;
            case EntityType::WITHER_SKULL: return "wither_skull"s;
            case EntityType::WOLF: return "wolf"s;
            case EntityType::ZOGLIN: return "zoglin"s;
            case EntityType::ZOMBIE: return "zombie"s;
            case EntityType::ZOMBIE_HORSE: return "zombie_horse"s;
            case EntityType::ZOMBIE_VILLAGER: return "zombie_villager"s;
            case EntityType::ZOMBIFIED_PIGLIN: return "zombified_piglin"s;
            case EntityType::PLAYER: return "player"s;
            case EntityType::FISHING_BOBBER: return "fishing_bobber"s;
            default: return {};
        }
    }
};

template<>
struct Json::Serialize<EntityClassification> {
    static auto to_json(const EntityClassification& entity) -> Json {
        using namespace std::string_literals;

        switch (entity) {
            case EntityClassification::MONSTER: return "monster"s;
            case EntityClassification::CREATURE: return "creature"s;
            case EntityClassification::AMBIENT: return "ambient"s;
            case EntityClassification::WATER_CREATURE: return "water_creature"s;
            case EntityClassification::WATER_AMBIENT: return "water_ambient"s;
            case EntityClassification::MISC: return "misc"s;
            default: return {};
        }
    }
};

template<>
struct Json::Serialize<MobSpawnInfo::SpawnCosts> {
    static auto to_json(const MobSpawnInfo::SpawnCosts& costs) -> Json {
        return {
            {"maxSpawnCost", costs.maxSpawnCost},
            {"entitySpawnCost", costs.entitySpawnCost}
        };
    }
};

template<>
struct Json::Serialize<MobSpawnInfo::Spawners> {
    static auto to_json(const MobSpawnInfo::Spawners& spawners) -> Json {
        return {
            {"type", spawners.type},
            {"weight", spawners.weight},
            {"min_count", spawners.minCount},
            {"max_count", spawners.maxCount},
        };
    }
};

void Biomes::registerBiomes() {
    using namespace std::string_literals;

    OCEAN = registerBiome(0, "ocean"s, BiomeMaker::makeOceanBiome(false));
    PLAINS = registerBiome(1, "plains"s, BiomeMaker::makePlainsBiome(false));
    DESERT = registerBiome(2, "desert"s, BiomeMaker::makeDesertBiome(0.125F, 0.05F, true, true, true));
    MOUNTAINS = registerBiome(3, "mountains"s, BiomeMaker::makeMountainBiome(1.0F, 0.5F, ConfiguredSurfaceBuilders::MOUNTAIN, false));
    FOREST = registerBiome(4, "forest"s, BiomeMaker::makeForestBiome(0.1F, 0.2F));
    TAIGA = registerBiome(5, "taiga"s, BiomeMaker::makeTaigaBiome(0.2F, 0.2F, false, false, true, false));
    SWAMP = registerBiome(6, "swamp"s,BiomeMaker::makeGenericSwampBiome(-0.2F, 0.1F, false));
    RIVER = registerBiome(7, "river"s, BiomeMaker::makeRiverBiome(-0.5F, 0.0F, 0.5F, 4159204, false));
    NETHER_WASTES = registerBiome(8, "nether_wastes"s, BiomeMaker::makeNetherWastesBiome());
    THE_END = registerBiome(9, "the_end"s, BiomeMaker::makeTheEndBiome());
    FROZEN_OCEAN = registerBiome(10, "frozen_ocean"s, BiomeMaker::makeFrozenOceanBiome(false));
    FROZEN_RIVER = registerBiome(11, "frozen_river"s, BiomeMaker::makeRiverBiome(-0.5F, 0.0F, 0.0F, 3750089, true));
    SNOWY_TUNDRA = registerBiome(12, "snowy_tundra"s, BiomeMaker::makeSnowyBiome(0.125F, 0.05F, false, false));
    SNOWY_MOUNTAINS = registerBiome(13, "snowy_mountains"s, BiomeMaker::makeSnowyBiome(0.45F, 0.3F, false, true));
    MUSHROOM_FIELDS = registerBiome(14, "mushroom_fields"s, BiomeMaker::makeMushroomBiome(0.2F, 0.3F));
    MUSHROOM_FIELD_SHORE = registerBiome(15, "mushroom_field_shore"s, BiomeMaker::makeMushroomBiome(0.0F, 0.025F));
    BEACH = registerBiome(16, "beach"s, BiomeMaker::makeBeachBiome(0.0F, 0.025F, 0.8F, 0.4F, 4159204, false, false));
    DESERT_HILLS = registerBiome(17, "desert_hills"s, BiomeMaker::makeDesertBiome(0.45F, 0.3F, false, true, false));
    WOODED_HILLS = registerBiome(18, "wooded_hills"s, BiomeMaker::makeForestBiome(0.45F, 0.3F));
    TAIGA_HILLS = registerBiome(19, "taiga_hills"s, BiomeMaker::makeTaigaBiome(0.45F, 0.3F, false, false, false, false));
    MOUNTAIN_EDGE = registerBiome(20, "mountain_edge"s, BiomeMaker::makeMountainBiome(0.8F, 0.3F, ConfiguredSurfaceBuilders::GRASS, true));
    JUNGLE = registerBiome(21, "jungle"s, BiomeMaker::makeJungleBiome());
    JUNGLE_HILLS = registerBiome(22, "jungle_hills"s, BiomeMaker::makeJungleHillsBiome());
    JUNGLE_EDGE = registerBiome(23, "jungle_edge"s, BiomeMaker::makeJungleEdgeBiome());
    DEEP_OCEAN = registerBiome(24, "deep_ocean"s, BiomeMaker::makeOceanBiome(true));
    STONE_SHORE = registerBiome(25, "stone_shore"s, BiomeMaker::makeBeachBiome(0.1F, 0.8F, 0.2F, 0.3F, 4159204, false, true));
    SNOWY_BEACH = registerBiome(26, "snowy_beach"s, BiomeMaker::makeBeachBiome(0.0F, 0.025F, 0.05F, 0.3F, 4020182, true, false));
    BIRCH_FOREST = registerBiome(27, "birch_forest"s, BiomeMaker::makeBirchForestBiome(0.1F, 0.2F, false));
    BIRCH_FOREST_HILLS = registerBiome(28, "birch_forest_hills"s, BiomeMaker::makeBirchForestBiome(0.45F, 0.3F, false));
    DARK_FOREST = registerBiome(29, "dark_forest"s, BiomeMaker::makeDarkForestBiome(0.1F, 0.2F, false));
    SNOWY_TAIGA = registerBiome(30, "snowy_taiga"s, BiomeMaker::makeTaigaBiome(0.2F, 0.2F, true, false, false, true));
    SNOWY_TAIGA_HILLS = registerBiome(31, "snowy_taiga_hills"s, BiomeMaker::makeTaigaBiome(0.45F, 0.3F, true, false, false, false));
    GIANT_TREE_TAIGA = registerBiome(32, "giant_tree_taiga"s, BiomeMaker::makeGiantTaigaBiome(0.2F, 0.2F, 0.3F, false));
    GIANT_TREE_TAIGA_HILLS = registerBiome(33, "giant_tree_taiga_hills"s, BiomeMaker::makeGiantTaigaBiome(0.45F, 0.3F, 0.3F, false));
    WOODED_MOUNTAINS = registerBiome(34, "wooded_mountains"s, BiomeMaker::makeMountainBiome(1.0F, 0.5F, ConfiguredSurfaceBuilders::GRASS, true));
    SAVANNA = registerBiome(35, "savanna"s, BiomeMaker::makeSavannaBiome(0.125F, 0.05F, 1.2F, false, false));
    SAVANNA_PLATEAU = registerBiome(36, "savanna_plateau"s, BiomeMaker::makeSavannaPlateauBiome());
    BADLANDS = registerBiome(37, "badlands"s, BiomeMaker::makeBadlandsBiome(0.1F, 0.2F, false));
    WOODED_BADLANDS_PLATEAU = registerBiome(38, "wooded_badlands_plateau"s, BiomeMaker::makeWoodedBadlandsPlateauBiome(1.5F, 0.025F));
    BADLANDS_PLATEAU = registerBiome(39, "badlands_plateau"s, BiomeMaker::makeBadlandsBiome(1.5F, 0.025F, true));
    SMALL_END_ISLANDS = registerBiome(40, "small_end_islands"s, BiomeMaker::makeSmallEndIslandsBiome());
    END_MIDLANDS = registerBiome(41, "end_midlands"s, BiomeMaker::makeEndMidlandsBiome());
    END_HIGHLANDS = registerBiome(42, "end_highlands"s, BiomeMaker::makeEndHighlandsBiome());
    END_BARRENS = registerBiome(43, "end_barrens"s, BiomeMaker::makeEndBarrensBiome());
    WARM_OCEAN = registerBiome(44, "warm_ocean"s, BiomeMaker::makeWarmOceanBiome());
    LUKEWARM_OCEAN = registerBiome(45, "lukewarm_ocean"s, BiomeMaker::makeLukewarmOceanBiome(false));
    COLD_OCEAN = registerBiome(46, "cold_ocean"s, BiomeMaker::makeColdOceanBiome(false));
    DEEP_WARM_OCEAN = registerBiome(47, "deep_warm_ocean"s,  BiomeMaker::makeDeepWarmOceanBiome());
    DEEP_LUKEWARM_OCEAN = registerBiome(48, "deep_lukewarm_ocean"s, BiomeMaker::makeLukewarmOceanBiome(true));
    DEEP_COLD_OCEAN = registerBiome(49, "deep_cold_ocean"s, BiomeMaker::makeColdOceanBiome(true));
    DEEP_FROZEN_OCEAN = registerBiome(50, "deep_frozen_ocean"s, BiomeMaker::makeFrozenOceanBiome(true));
    THE_VOID = registerBiome(127, "the_void"s, BiomeMaker::makeVoidBiome());
    SUNFLOWER_PLAINS = registerBiome(129, "sunflower_plains"s, BiomeMaker::makePlainsBiome(true));
    DESERT_LAKES = registerBiome(130, "desert_lakes"s, BiomeMaker::makeDesertBiome(0.225F, 0.25F, false, false, false));
    GRAVELLY_MOUNTAINS = registerBiome(131, "gravelly_mountains"s, BiomeMaker::makeMountainBiome(1.0F, 0.5F, ConfiguredSurfaceBuilders::GRAVELLY_MOUNTAIN, false));
    FLOWER_FOREST = registerBiome(132, "flower_forest"s, BiomeMaker::makeFlowerForestBiome());
    TAIGA_MOUNTAINS = registerBiome(133, "taiga_mountains"s, BiomeMaker::makeTaigaBiome(0.3F, 0.4F, false, true, false, false));
    SWAMP_HILLS = registerBiome(134, "swamp_hills"s, BiomeMaker::makeGenericSwampBiome(-0.1F, 0.3F, true));
    ICE_SPIKES = registerBiome(140, "ice_spikes"s, BiomeMaker::makeSnowyBiome(0.425F, 0.45000002F, true, false));
    MODIFIED_JUNGLE = registerBiome(149, "modified_jungle"s, BiomeMaker::makeModifiedJungleBiome());
    MODIFIED_JUNGLE_EDGE = registerBiome(151, "modified_jungle_edge"s, BiomeMaker::makeModifiedJungleEdgeBiome());
    TALL_BIRCH_FOREST = registerBiome(155, "tall_birch_forest"s, BiomeMaker::makeBirchForestBiome(0.2F, 0.4F, true));
    TALL_BIRCH_HILLS = registerBiome(156, "tall_birch_hills"s, BiomeMaker::makeBirchForestBiome(0.55F, 0.5F, true));
    DARK_FOREST_HILLS = registerBiome(157, "dark_forest_hills"s, BiomeMaker::makeDarkForestBiome(0.2F, 0.4F, true));
    SNOWY_TAIGA_MOUNTAINS = registerBiome(158, "snowy_taiga_mountains"s, BiomeMaker::makeTaigaBiome(0.3F, 0.4F, true, true, false, false));
    GIANT_SPRUCE_TAIGA = registerBiome(160, "giant_spruce_taiga"s, BiomeMaker::makeGiantTaigaBiome(0.2F, 0.2F, 0.25F, true));
    GIANT_SPRUCE_TAIGA_HILLS = registerBiome(161, "giant_spruce_taiga_hills"s, BiomeMaker::makeGiantTaigaBiome(0.2F, 0.2F, 0.25F, true));
    MODIFIED_GRAVELLY_MOUNTAINS = registerBiome(162, "modified_gravelly_mountains"s, BiomeMaker::makeMountainBiome(1.0, 0.5, ConfiguredSurfaceBuilders::GRAVELLY_MOUNTAIN, false));
    SHATTERED_SAVANNA = registerBiome(163, "shattered_savanna"s, BiomeMaker::makeSavannaBiome(0.3625F, 1.225F, 1.1F, true, true));
    SHATTERED_SAVANNA_PLATEAU = registerBiome(164, "shattered_savanna_plateau"s, BiomeMaker::makeSavannaBiome(1.05F, 1.2125001F, 1.0F, true, true));
    ERODED_BADLANDS = registerBiome(165, "eroded_badlands"s, BiomeMaker::makeErodedBadlandsBiome());
    MODIFIED_WOODED_BADLANDS_PLATEAU = registerBiome(166, "modified_wooded_badlands_plateau"s, BiomeMaker::makeWoodedBadlandsPlateauBiome(0.45, 0.3));
    MODIFIED_BADLANDS_PLATEAU = registerBiome(167, "modified_badlands_plateau"s, BiomeMaker::makeBadlandsBiome(0.45, 0.3, true));
    BAMBOO_JUNGLE = registerBiome(168, "bamboo_jungle"s, BiomeMaker::makeBambooJungleBiome());
    BAMBOO_JUNGLE_HILLS = registerBiome(169, "bamboo_jungle_hills"s, BiomeMaker::makeBambooJungleHillsBiome());
    SOUL_SAND_VALLEY = registerBiome(170, "soul_sand_valley"s, BiomeMaker::makeSoulSandValleyBiome());
    CRIMSON_FOREST = registerBiome(171, "crimson_forest"s, BiomeMaker::makeCrimsonForestBiome());
    WARPED_FOREST = registerBiome(172, "warped_forest"s, BiomeMaker::makeWarpedForestBiome());
    BASALT_DELTAS = registerBiome(173, "basalt_deltas"s, BiomeMaker::makeBasaltDeltasBiome());

    for (const auto& [name, biome] : Biomes::biomes.objects) {
        std::ofstream out{fmt::format("definitions/biomes/{}.json", name), std::ios::binary};
        out << Json{
            {"depth", biome->depth},
            {"scale", biome->scale},
            {"precipitation", biome->climate.precipitation},
            {"category", biome->category},
            {"temperature", biome->climate.temperature},
            {"temperature_modifier", biome->climate.temperatureModifier},
            {"downfall", biome->climate.downfall},
            {"player_spawn_friendly", biome->mobSpawnInfo.playerSpawnFriendly},
			{"creature_spawn_probability", biome->mobSpawnInfo.creatureSpawnProbability},
            {"effects", biome->effects},
            {"surface_builder", biome->biomeGenerationSettings.surfaceBuilder},
            {"carvers", biome->biomeGenerationSettings.carvers},
            {"features", biome->biomeGenerationSettings.features},
            {"structures", biome->biomeGenerationSettings.structures},
            {"spawners", biome->mobSpawnInfo.spawners},
            {"spawn_costs", biome->mobSpawnInfo.spawnCosts}
        };
    }
}