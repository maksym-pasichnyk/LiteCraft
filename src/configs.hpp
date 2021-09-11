#pragma once

#include <json/json.hpp>

#include <world/biome/BiomeClimate.hpp>
#include <world/biome/BiomeCategory.hpp>
#include <world/biome/BiomeAmbience.hpp>
#include <world/biome/GrassColorModifiers.hpp>
#include <world/biome/TemperatureModifiers.hpp>
#include <world/biome/BiomeGenerationSettings.hpp>
#include <world/gen/placement/Placements.hpp>
#include <world/gen/carver/Carvers.hpp>
#include <world/gen/carver/ConfiguredCarvers.hpp>
#include <world/gen/surface/SurfaceBuilder.hpp>
#include <world/gen/surface/ConfiguredSurfaceBuilders.hpp>
#include <world/gen/feature/Features.hpp>
#include <world/gen/feature/ConfiguredFeatures.hpp>
#include <world/gen/feature/structure/Structures.hpp>
#include <world/gen/feature/structure/StructureFeatures.hpp>

template <>
struct Json::Serialize<RainType> {
    static auto to_json(const RainType& type) -> Json {
        using namespace std::string_literals;

        switch (type) {
            case RainType::NONE: return "none"s;
            case RainType::RAIN: return "rain"s;
            case RainType::SNOW: return "snow"s;
            default: return {};
        }
    }
};

template <>
struct Json::Deserialize<RainType> {
    static auto from_json(const Json& obj) -> std::optional<RainType> {
        using namespace std::string_literals;

        static auto table = std::map<std::string, RainType> {
            {"none"s, RainType::NONE},
            {"rain"s, RainType::RAIN},
            {"snow"s, RainType::SNOW}
        };

        if (auto it = table.find(obj.to_string()); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <>
struct Json::Serialize<BiomeCategory> {
    static auto to_json(const BiomeCategory& category) -> Json {
        using namespace std::string_literals;

        switch (category) {
            case BiomeCategory::NONE: return "none"s;
            case BiomeCategory::TAIGA: return "taiga"s;
            case BiomeCategory::EXTREME_HILLS: return "extreme_hills"s;
            case BiomeCategory::JUNGLE: return "jungle"s;
            case BiomeCategory::MESA: return "mesa"s;
            case BiomeCategory::PLAINS: return "plains"s;
            case BiomeCategory::SAVANNA: return "savanna"s;
            case BiomeCategory::ICY: return "icy"s;
            case BiomeCategory::THEEND: return "theend"s;
            case BiomeCategory::BEACH: return "beach"s;
            case BiomeCategory::FOREST: return "forest"s;
            case BiomeCategory::OCEAN: return "ocean"s;
            case BiomeCategory::DESERT: return "desert"s;
            case BiomeCategory::RIVER: return "river"s;
            case BiomeCategory::SWAMP: return "swamp"s;
            case BiomeCategory::MUSHROOM: return "mushroom"s;
            case BiomeCategory::NETHER: return "nether"s;
            default: return {};
        }
    }
};

template <>
struct Json::Serialize<RuinedPortalLocation> {
    static auto to_json(const RuinedPortalLocation& location) -> Json {
        using namespace std::string_literals;

        switch (location) {
            case RuinedPortalLocation::STANDARD: return "standard"s;
            case RuinedPortalLocation::DESERT: return "desert"s;
            case RuinedPortalLocation::JUNGLE: return "jungle"s;
            case RuinedPortalLocation::SWAMP: return "swamp"s;
            case RuinedPortalLocation::MOUNTAIN: return "mountain"s;
            case RuinedPortalLocation::OCEAN: return "ocean"s;
            case RuinedPortalLocation::NETHER: return "nether"s;
            default: return {};
        }
    }
};

template <>
struct Json::Serialize<OceanRuinType> {
    static auto to_json(const OceanRuinType& type) -> Json {
        using namespace std::string_literals;

        switch (type) {
            case OceanRuinType::WARM: return "warm"s;
            case OceanRuinType::COLD: return "cold"s;
            default: return {};
        }
    }
};

template <>
struct Json::Deserialize<BiomeCategory> {
    static auto from_json(const Json &obj) -> std::optional<BiomeCategory> {
        using namespace std::string_literals;

        static auto table = std::map<std::string, BiomeCategory> {
            {"none"s, BiomeCategory::NONE},
            {"taiga"s, BiomeCategory::TAIGA},
            {"extreme_hills"s, BiomeCategory::EXTREME_HILLS},
            {"jungle"s, BiomeCategory::JUNGLE},
            {"mesa"s, BiomeCategory::MESA},
            {"plains"s, BiomeCategory::PLAINS},
            {"savanna"s, BiomeCategory::SAVANNA},
            {"icy"s, BiomeCategory::ICY},
            {"theend"s, BiomeCategory::THEEND},
            {"beach"s, BiomeCategory::BEACH},
            {"forest"s, BiomeCategory::FOREST},
            {"ocean"s, BiomeCategory::OCEAN},
            {"desert"s, BiomeCategory::DESERT},
            {"river"s, BiomeCategory::RIVER},
            {"swamp"s, BiomeCategory::SWAMP},
            {"mushroom"s, BiomeCategory::MUSHROOM},
            {"nether"s, BiomeCategory::NETHER}
        };

        if (auto it = table.find(obj.to_string()); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template<>
struct Json::Serialize<TemperatureModifier> {
    static auto to_json(const TemperatureModifier& modifier) -> Json {
        using namespace std::string_literals;

        if (modifier == TemperatureModifiers::none) {
            return "none"s;
        }
        if (modifier == TemperatureModifiers::frozen) {
            return "frozen"s;
        }
        return {};
    }
};

template <>
struct Json::Deserialize<TemperatureModifier> {
    static auto from_json(const Json& obj) -> std::optional<TemperatureModifier> {
        using namespace std::string_literals;

        static auto table = std::map<std::string, TemperatureModifier> {
            {"none"s, TemperatureModifiers::none},
            {"frozen"s, TemperatureModifiers::frozen}
        };

        if (auto it = table.find(obj.to_string()); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template<>
struct Json::Serialize<GrassColorModifier> {
    static auto to_json(const GrassColorModifier& modifier) -> Json {
        using namespace std::string_literals;

        if (modifier == GrassColorModifiers::none) {
            return "none"s;
        }
        if (modifier == GrassColorModifiers::swamp) {
            return "swamp"s;
        }
        if (modifier == GrassColorModifiers::dark_forest) {
            return "dark_forest"s;
        }
        return {};
    }
};

template <>
struct Json::Deserialize<GrassColorModifier> {
    static auto from_json(const Json& obj) -> std::optional<GrassColorModifier> {
        using namespace std::string_literals;

        static auto table = std::map<std::string, GrassColorModifier> {
            {"none"s, GrassColorModifiers::none},
            {"swamp"s, GrassColorModifiers::swamp},
            {"dark_forest"s, GrassColorModifiers::dark_forest}
        };

        if (auto it = table.find(obj.to_string()); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <>
struct Json::Serialize<ParticleType> {
    static auto to_json(const ParticleType& type) -> Json {
        using namespace std::string_literals;

        switch (type) {
            case ParticleType::AMBIENT_ENTITY_EFFECT: return "ambient_entity_effect"s;
            case ParticleType::ANGRY_VILLAGER: return "angry_villager"s;
            case ParticleType::BARRIER: return "barrier"s;
            case ParticleType::BLOCK: return "block"s;
            case ParticleType::BUBBLE: return "bubble"s;
            case ParticleType::CLOUD: return "cloud"s;
            case ParticleType::CRIT: return "crit"s;
            case ParticleType::DAMAGE_INDICATOR: return "damage_indicator"s;
            case ParticleType::DRAGON_BREATH: return "dragon_breath"s;
            case ParticleType::DRIPPING_LAVA: return "dripping_lava"s;
            case ParticleType::FALLING_LAVA: return "falling_lava"s;
            case ParticleType::LANDING_LAVA: return "landing_lava"s;
            case ParticleType::DRIPPING_WATER: return "dripping_water"s;
            case ParticleType::FALLING_WATER: return "falling_water"s;
            case ParticleType::DUST: return "dust"s;
            case ParticleType::EFFECT: return "effect"s;
            case ParticleType::ELDER_GUARDIAN: return "elder_guardian"s;
            case ParticleType::ENCHANTED_HIT: return "enchanted_hit"s;
            case ParticleType::ENCHANT: return "enchant"s;
            case ParticleType::END_ROD: return "end_rod"s;
            case ParticleType::ENTITY_EFFECT: return "entity_effect"s;
            case ParticleType::EXPLOSION_EMITTER: return "explosion_emitter"s;
            case ParticleType::EXPLOSION: return "explosion"s;
            case ParticleType::FALLING_DUST: return "falling_dust"s;
            case ParticleType::FIREWORK: return "firework"s;
            case ParticleType::FISHING: return "fishing"s;
            case ParticleType::FLAME: return "flame"s;
            case ParticleType::SOUL_FIRE_FLAME: return "soul_fire_flame"s;
            case ParticleType::SOUL: return "soul"s;
            case ParticleType::FLASH: return "flash"s;
            case ParticleType::HAPPY_VILLAGER: return "happy_villager"s;
            case ParticleType::COMPOSTER: return "composter"s;
            case ParticleType::HEART: return "heart"s;
            case ParticleType::INSTANT_EFFECT: return "instant_effect"s;
            case ParticleType::ITEM: return "item"s;
            case ParticleType::ITEM_SLIME: return "item_slime"s;
            case ParticleType::ITEM_SNOWBALL: return "item_snowball"s;
            case ParticleType::LARGE_SMOKE: return "large_smoke"s;
            case ParticleType::LAVA: return "lava"s;
            case ParticleType::MYCELIUM: return "mycelium"s;
            case ParticleType::NOTE: return "note"s;
            case ParticleType::POOF: return "poof"s;
            case ParticleType::PORTAL: return "portal"s;
            case ParticleType::RAIN: return "rain"s;
            case ParticleType::SMOKE: return "smoke"s;
            case ParticleType::SNEEZE: return "sneeze"s;
            case ParticleType::SPIT: return "spit"s;
            case ParticleType::SQUID_INK: return "squid_ink"s;
            case ParticleType::SWEEP_ATTACK: return "sweep_attack"s;
            case ParticleType::TOTEM_OF_UNDYING: return "totem_of_undying"s;
            case ParticleType::UNDERWATER: return "underwater"s;
            case ParticleType::SPLASH: return "splash"s;
            case ParticleType::WITCH: return "witch"s;
            case ParticleType::BUBBLE_POP: return "bubble_pop"s;
            case ParticleType::CURRENT_DOWN: return "current_down"s;
            case ParticleType::BUBBLE_COLUMN_UP: return "bubble_column_up"s;
            case ParticleType::NAUTILUS: return "nautilus"s;
            case ParticleType::DOLPHIN: return "dolphin"s;
            case ParticleType::CAMPFIRE_COSY_SMOKE: return "campfire_cosy_smoke"s;
            case ParticleType::CAMPFIRE_SIGNAL_SMOKE: return "campfire_signal_smoke"s;
            case ParticleType::DRIPPING_HONEY: return "dripping_honey"s;
            case ParticleType::FALLING_HONEY: return "falling_honey"s;
            case ParticleType::LANDING_HONEY: return "landing_honey"s;
            case ParticleType::FALLING_NECTAR: return "falling_nectar"s;
            case ParticleType::ASH: return "ash"s;
            case ParticleType::CRIMSON_SPORE: return "crimson_spore"s;
            case ParticleType::WARPED_SPORE: return "warped_spore"s;
            case ParticleType::DRIPPING_OBSIDIAN_TEAR: return "dripping_obsidian_tear"s;
            case ParticleType::FALLING_OBSIDIAN_TEAR: return "falling_obsidian_tear"s;
            case ParticleType::LANDING_OBSIDIAN_TEAR: return "landing_obsidian_tear"s;
            case ParticleType::REVERSE_PORTAL: return "reverse_portal"s;
            case ParticleType::WHITE_ASH: return "white_ash"s;
            case ParticleType::REDSTONE_DUST: return "redstone_dust"s;
            default: return {};
        }
    }
};

template <>
struct Json::Serialize<SoundEvent> {
    static auto to_json(const SoundEvent& sound) -> Json {
        return sound.location;
    }
};

template<>
struct Json::Serialize<ParticleEffectAmbience> {
    static auto to_json(const ParticleEffectAmbience &effect) -> Json {
        return {
            {"type", effect.type},
            {"probability", effect.probability}
        };
    }
};

template<>
struct Json::Serialize<MoodSoundAmbience> {
    static auto to_json(const MoodSoundAmbience &sound) -> Json {
        return {
            {"sound", sound.sound},
            {"delay", sound.delay},
            {"radius", sound.radius},
            {"offset", sound.offset}
        };
    }
};

template<>
struct Json::Serialize<SoundAdditionsAmbience> {
    static auto to_json(const SoundAdditionsAmbience &sound) -> Json {
        return {
            {"sound", sound.sound},
            {"chance", sound.chance}
        };
    }
};

template<>
struct Json::Serialize<BackgroundMusicTrack> {
    static auto to_json(const BackgroundMusicTrack &track) -> Json {
        return {
            { "sound", track.sound},
            { "min_delay", track.minDelay},
            { "max_delay", track.maxDelay},
            { "replace_current_music", track.replaceCurrentMusic},
        };
    }
};

template<>
struct Json::Serialize<BiomeAmbience> {
    static auto to_json(const BiomeAmbience &ambience) -> Json {
        auto obj = Json::Object{};
        obj["fog_color"] = ambience.fogColor;
        obj["water_color"] = ambience.waterColor;
        obj["water_fog_color"] = ambience.waterFogColor;
        obj["sky_color"] = ambience.skyColor;
        obj["fog_color"] = ambience.fogColor;

        if (ambience.foliageColor.has_value()) {
            obj["foliage_color"] = *ambience.foliageColor;
        }
        if (ambience.grassColor.has_value()) {
            obj["grass_color"] = *ambience.grassColor;
        }

        obj["grass_color_modifier"] = ambience.grassColorModifier;

        if (ambience.particle.has_value()) {
            obj["particle"] = *ambience.particle;
        }

        if (ambience.ambientSound.has_value()) {
            obj["ambient_sound"] = *ambience.ambientSound;
        }

        if (ambience.additionsSound.has_value()) {
            obj["additions_sound"] = *ambience.additionsSound;
        }

        if (ambience.music.has_value()) {
            obj["music"] = *ambience.music;
        }

        return std::move(obj);
    }
};

template<>
struct Json::Deserialize<BiomeAmbience> {
    static auto from_json(const Json& obj) -> std::optional<BiomeAmbience> {
        auto&& o = obj.to_object();

        auto foliage_color = o.find("foliage_color");
        auto grass_color = o.find("grass_color");
        auto particle = o.find("particle");
        auto ambient_sound = o.find("ambient_sound");
        auto additions_sound = o.find("additions_sound");
        auto music = o.find("music");

        return BiomeAmbience{
            .fogColor = o.at("fog_color"),
            .waterColor = o.at("water_color"),
            .waterFogColor = o.at("water_fog_color"),
            .skyColor = o.at("sky_color"),
//            .foliageColor = foliage_color != o.end() ? std::optional(foliage_color->second) : std::nullopt
        };
    }
};

//template<>
//struct Json::Serialize<BiomeClimate> {
//    static auto to_json(const BiomeClimate &climate) -> Json {
//        return {
//            {"precipitation", climate.precipitation},
//            {"temperature", climate.temperature},
//            {"temperature_modifier", climate.temperatureModifier},
//            {"downfall", climate.downfall}
//        };
//    }
//};

//template<>
//struct Json::Deserialize<BiomeClimate> {
//    static auto from_json(const Json& obj) -> std::optional<BiomeClimate> {
//        auto&& o = obj.to_object();
//        return BiomeClimate{
//            .precipitation = o.at("precipitation"),
//            .temperature = o.at("temperature"),
//            .temperatureModifier = o.at("temperature_modifier"),
//            .downfall = o.at("downfall")
//        };
//    }
//};

template<>
struct Json::Serialize<SurfaceBuilder*> {
    static auto to_json(SurfaceBuilder* builder) -> Json {
        return SurfaceBuilder::builders.name(builder).value();
    }
};

template<>
struct Json::Deserialize<SurfaceBuilder*> {
    static auto from_json(const Json& obj) -> std::optional<SurfaceBuilder*> {
        return SurfaceBuilder::builders.get(obj.to_string());
    }
};

template<>
struct Json::Serialize<ConfiguredSurfaceBuilder*> {
    static auto to_json(ConfiguredSurfaceBuilder* builder) -> Json {
        return ConfiguredSurfaceBuilders::builders.name(builder).value();
    }
};

template<>
struct Json::Deserialize<ConfiguredSurfaceBuilder*> {
    static auto from_json(const Json& obj) -> std::optional<ConfiguredSurfaceBuilder*> {
        return ConfiguredSurfaceBuilders::builders.get(obj.to_string());
    }
};

template<>
struct Json::Serialize<ConfiguredFeature*> {
    static auto to_json(ConfiguredFeature* feature) -> Json {
        return ConfiguredFeatures::features.name(feature).value();
    }
};

template<>
struct Json::Deserialize<ConfiguredFeature*> {
    static auto from_json(const Json& obj) -> std::optional<ConfiguredFeature*> {
        return ConfiguredFeatures::features.get(obj.to_string());
    }
};

template<>
struct Json::Serialize<Structure*> {
    static auto to_json(Structure* structure) -> Json {
        return Structures::registry.name(structure).value();
    }
};

template<>
struct Json::Deserialize<Structure*> {
    static auto from_json(const Json& obj) -> std::optional<Structure*> {
        return Structures::registry.get(obj.to_string());
    }
};

template<>
struct Json::Serialize<StructureFeature*> {
    static auto to_json(StructureFeature* structure) -> Json {
        return StructureFeatures::registry.name(structure).value();
    }
};

template<>
struct Json::Deserialize<StructureFeature*> {
    static auto from_json(const Json& obj) -> std::optional<StructureFeature*> {
        return StructureFeatures::registry.get(obj.to_string());
    }
};

template<>
struct Json::Serialize<ConfiguredCarver*> {
    static auto to_json(ConfiguredCarver* carver) -> Json {
        return ConfiguredCarvers::carvers.name(carver).value();
    }
};

template<>
struct Json::Deserialize<ConfiguredCarver*> {
    static auto from_json(const Json& obj) -> std::optional<ConfiguredCarver*> {
        return ConfiguredCarvers::carvers.get(obj.to_string());
    }
};

//template<>
//struct Json::Serialize<BiomeGenerationSettings> {
//    static auto to_json(const BiomeGenerationSettings &settings) -> Json {
//        return {
//            {"surface", settings.surfaceBuilder},
//            {"carvers", settings.carvers},
//            {"features", settings.features},
//            {"structures", settings.structures}
//        };
//    }
//};

//template<>
//struct Json::Deserialize<BiomeGenerationSettings> {
//    static auto from_json(const Json& obj) -> std::optional<BiomeGenerationSettings> {
//        auto&& o = obj.to_object();
//        return BiomeGenerationSettings{
//            .surfaceBuilder = o.at("surface"),
//            .carvers = o.at("carvers"),
//            .features = o.at("features"),
//            .structures = o.at("structures")
//        };
//    }
//};

template<>
struct Json::Serialize<RuinedPortalConfig> {
    static auto to_json(const RuinedPortalConfig &config) -> Json {
        return {
            {"location", config.location},
        };
    }
};

template<>
struct Json::Serialize<VillageConfig> {
    static auto to_json(const VillageConfig &config) -> Json {
        return Json::Object{};
    }
};

template<>
struct Json::Serialize<ShipwreckConfig> {
    static auto to_json(const ShipwreckConfig &config) -> Json {
        return {
            {"is_beached", config.isBeached}
        };
    }
};

template<>
struct Json::Serialize<OceanRuinConfig> {
    static auto to_json(const OceanRuinConfig &config) -> Json {
        return {
            {"type", config.type},
            {"large_probability", config.largeProbability},
            {"cluster_probability", config.clusterProbability}
        };
    }
};

template<>
struct Json::Serialize<ProbabilityConfig> {
    static auto to_json(const ProbabilityConfig &config) -> Json {
        return {
            {"probability", config.probability}
        };
    }
};

template<>
struct Json::Deserialize<ProbabilityConfig> {
    static auto from_json(const Json& obj) -> std::optional<ProbabilityConfig> {
        auto&& o = obj.to_object();
        return ProbabilityConfig{
            .probability = o.at("probability")
        };
    }
};

template<>
struct Json::Serialize<WorldCarver*> {
    static auto to_json(WorldCarver* carver) -> Json {
        return Carvers::carvers.name(carver).value();
    }
};

template<>
struct Json::Deserialize<WorldCarver*> {
    static auto from_json(const Json& obj) -> std::optional<WorldCarver*> {
        return Carvers::carvers.get(obj.to_string());
    }
};