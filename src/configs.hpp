#pragma once

#include <Json.hpp>

#include <entity/EntityClassification.hpp>
#include <entity/EntityType.hpp>
#include <world/biome/BiomeAmbience.hpp>
#include <world/biome/BiomeCategory.hpp>
#include <world/biome/BiomeClimate.hpp>
#include <world/biome/BiomeGenerationSettings.hpp>
#include <world/biome/GrassColorModifiers.hpp>
#include <world/biome/MobSpawnInfo.hpp>
#include <world/biome/TemperatureModifiers.hpp>
#include <world/gen/carver/Carvers.hpp>
#include <world/gen/carver/ConfiguredCarvers.hpp>
#include <world/gen/feature/ConfiguredFeatures.hpp>
#include <world/gen/feature/Features.hpp>
#include <world/gen/feature/jigsaw/JigsawPattern.hpp>
#include <world/gen/feature/jigsaw/JigsawProjection.hpp>
#include <world/gen/feature/structure/StructureFeatures.hpp>
#include <world/gen/feature/structure/Structures.hpp>
#include <world/gen/placement/Placements.hpp>
#include <world/gen/surface/ConfiguredSurfaceBuilders.hpp>
#include <world/gen/surface/SurfaceBuilders.hpp>
#include <world/gen/pools/JigsawPools.hpp>


template <>
struct Json::From<RainType> {
    static auto from(const RainType& type) -> Json {
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
struct Json::Into<RainType> {
    static auto into(const Json& obj) -> std::optional<RainType> {
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
struct Json::From<BiomeCategory> {
    static auto from(const BiomeCategory& category) -> Json {
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
struct Json::From<RuinedPortalLocation> {
    static auto from(const RuinedPortalLocation& location) -> Json {
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
struct Json::Into<RuinedPortalLocation> {
    static auto into(const Json& obj) -> std::optional<RuinedPortalLocation> {
        using namespace std::string_literals;

        static auto table = std::map<std::string, RuinedPortalLocation> {
            {"standard"s, RuinedPortalLocation::STANDARD},
            {"desert"s, RuinedPortalLocation::DESERT},
            {"jungle"s, RuinedPortalLocation::JUNGLE},
            {"swamp"s, RuinedPortalLocation::SWAMP},
            {"mountain"s, RuinedPortalLocation::MOUNTAIN},
            {"ocean"s, RuinedPortalLocation::OCEAN},
            {"nether"s, RuinedPortalLocation::NETHER}
        };

        if (auto it = table.find(obj.to_string()); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <>
struct Json::From<JigsawProjection> {
    static auto from(const JigsawProjection& projection) -> Json {
        using namespace std::string_literals;

        switch (projection) {
            case JigsawProjection::RIGID: return "rigid"s;
            case JigsawProjection::TERRAIN_MATCHING: return "terrain_matching"s;
            default: return {};
        }
    }
};

template <>
struct Json::Into<JigsawProjection> {
    static auto into(const Json& obj) -> std::optional<JigsawProjection> {
        using namespace std::string_literals;

        static auto table = std::map<std::string, JigsawProjection> {
            {"rigid"s, JigsawProjection::RIGID},
            {"terrain_matching"s, JigsawProjection::TERRAIN_MATCHING}
        };

        if (auto it = table.find(obj.to_string()); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <>
struct Json::From<OceanRuinType> {
    static auto from(const OceanRuinType& type) -> Json {
        using namespace std::string_literals;

        switch (type) {
            case OceanRuinType::WARM: return "warm"s;
            case OceanRuinType::COLD: return "cold"s;
            default: return {};
        }
    }
};

template <>
struct Json::Into<OceanRuinType> {
    static auto into(const Json& obj) -> std::optional<OceanRuinType> {
        using namespace std::string_literals;

        static auto table = std::map<std::string, OceanRuinType> {
            {"warm"s, OceanRuinType::WARM},
            {"cold"s, OceanRuinType::COLD}
        };

        if (auto it = table.find(obj.to_string()); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template<>
struct Json::From<NoFeatureConfig> {
    static auto from(const NoFeatureConfig &config) -> Json {
        return Json::Object{};
    }
};

template<>
struct Json::From<MineshaftType> {
    static auto from(const MineshaftType &type) -> Json {
        using namespace std::string_literals;
        switch (type) {
            case MineshaftType::NORMAL: return "normal"s;
            case MineshaftType::MESA: return "mesa"s;
            default: return {};
        }
    }
};

template<>
struct Json::Into<MineshaftType> {
    static auto into(const Json& obj) -> std::optional<MineshaftType> {
        using namespace std::string_literals;

        static auto table = std::map<std::string, MineshaftType> {
            {"normal"s, MineshaftType::NORMAL},
            {"mesa"s, MineshaftType::MESA}
        };

        if (auto it = table.find(obj.to_string()); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};


template<>
struct Json::From<MineshaftConfig> {
    static auto from(const MineshaftConfig& config) -> Json {
        return {
            {"probability", config.probability},
            {"type", config.type}
        };
    }
};

template<>
struct Json::Into<MineshaftConfig> {
    static auto into(const Json& obj) -> std::optional<MineshaftConfig> {
        auto&& o = obj.to_object();
        return MineshaftConfig{
            .probability = o.at("probability"),
            .type = o.at("type")
        };
    }
};

template<>
struct Json::Into<NoFeatureConfig> {
    static auto into(const Json& obj) -> std::optional<NoFeatureConfig> {
        return NoFeatureConfig{};
    }
};

template<>
struct Json::From<StructureConfig> {
    static auto from(const StructureConfig &config) -> Json {
        return match(config, []<typename T>(T&& cfg) -> Json {
            return {};
//            return std::forward<T>(cfg);
        });
    }
};


template <>
struct Json::Into<BiomeCategory> {
    static auto into(const Json &obj) -> std::optional<BiomeCategory> {
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
struct Json::From<TemperatureModifier> {
    static auto from(const TemperatureModifier& modifier) -> Json {
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
struct Json::Into<TemperatureModifier> {
    static auto into(const Json& obj) -> std::optional<TemperatureModifier> {
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
struct Json::From<GrassColorModifier> {
    static auto from(const GrassColorModifier& modifier) -> Json {
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
struct Json::Into<GrassColorModifier> {
    static auto into(const Json& obj) -> std::optional<GrassColorModifier> {
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
struct Json::From<ParticleType> {
    static auto from(const ParticleType& type) -> Json {
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
struct Json::Into<ParticleType> {
    static auto into(const Json& obj) -> std::optional<ParticleType> {
        using namespace std::string_literals;

        static auto table = std::map<std::string, ParticleType> {
            { "ambient_entity_effect"s, ParticleType::AMBIENT_ENTITY_EFFECT },
            { "angry_villager"s, ParticleType::ANGRY_VILLAGER },
            { "barrier"s, ParticleType::BARRIER },
            { "block"s, ParticleType::BLOCK },
            { "bubble"s, ParticleType::BUBBLE },
            { "cloud"s, ParticleType::CLOUD },
            { "crit"s, ParticleType::CRIT },
            { "damage_indicator"s, ParticleType::DAMAGE_INDICATOR },
            { "dragon_breath"s, ParticleType::DRAGON_BREATH },
            { "dripping_lava"s, ParticleType::DRIPPING_LAVA },
            { "falling_lava"s, ParticleType::FALLING_LAVA },
            { "landing_lava"s, ParticleType::LANDING_LAVA },
            { "dripping_water"s, ParticleType::DRIPPING_WATER },
            { "falling_water"s, ParticleType::FALLING_WATER },
            { "dust"s, ParticleType::DUST },
            { "effect"s, ParticleType::EFFECT },
            { "elder_guardian"s, ParticleType::ELDER_GUARDIAN },
            { "enchanted_hit"s, ParticleType::ENCHANTED_HIT },
            { "enchant"s, ParticleType::ENCHANT },
            { "end_rod"s, ParticleType::END_ROD },
            { "entity_effect"s, ParticleType::ENTITY_EFFECT },
            { "explosion_emitter"s, ParticleType::EXPLOSION_EMITTER },
            { "explosion"s, ParticleType::EXPLOSION },
            { "falling_dust"s, ParticleType::FALLING_DUST },
            { "firework"s, ParticleType::FIREWORK },
            { "fishing"s, ParticleType::FISHING },
            { "flame"s, ParticleType::FLAME },
            { "soul_fire_flame"s, ParticleType::SOUL_FIRE_FLAME },
            { "soul"s, ParticleType::SOUL },
            { "flash"s, ParticleType::FLASH },
            { "happy_villager"s, ParticleType::HAPPY_VILLAGER },
            { "composter"s, ParticleType::COMPOSTER },
            { "heart"s, ParticleType::HEART },
            { "instant_effect"s, ParticleType::INSTANT_EFFECT },
            { "item"s, ParticleType::ITEM },
            { "item_slime"s, ParticleType::ITEM_SLIME },
            { "item_snowball"s, ParticleType::ITEM_SNOWBALL },
            { "large_smoke"s, ParticleType::LARGE_SMOKE },
            { "lava"s, ParticleType::LAVA },
            { "mycelium"s, ParticleType::MYCELIUM },
            { "note"s, ParticleType::NOTE },
            { "poof"s, ParticleType::POOF },
            { "portal"s, ParticleType::PORTAL },
            { "rain"s, ParticleType::RAIN },
            { "smoke"s, ParticleType::SMOKE },
            { "sneeze"s, ParticleType::SNEEZE },
            { "spit"s, ParticleType::SPIT },
            { "squid_ink"s, ParticleType::SQUID_INK },
            { "sweep_attack"s, ParticleType::SWEEP_ATTACK },
            { "totem_of_undying"s, ParticleType::TOTEM_OF_UNDYING },
            { "underwater"s, ParticleType::UNDERWATER },
            { "splash"s, ParticleType::SPLASH },
            { "witch"s, ParticleType::WITCH },
            { "bubble_pop"s, ParticleType::BUBBLE_POP },
            { "current_down"s, ParticleType::CURRENT_DOWN },
            { "bubble_column_up"s, ParticleType::BUBBLE_COLUMN_UP },
            { "nautilus"s, ParticleType::NAUTILUS },
            { "dolphin"s, ParticleType::DOLPHIN },
            { "campfire_cosy_smoke"s, ParticleType::CAMPFIRE_COSY_SMOKE },
            { "campfire_signal_smoke"s, ParticleType::CAMPFIRE_SIGNAL_SMOKE },
            { "dripping_honey"s, ParticleType::DRIPPING_HONEY },
            { "falling_honey"s, ParticleType::FALLING_HONEY },
            { "landing_honey"s, ParticleType::LANDING_HONEY },
            { "falling_nectar"s, ParticleType::FALLING_NECTAR },
            { "ash"s, ParticleType::ASH },
            { "crimson_spore"s, ParticleType::CRIMSON_SPORE },
            { "warped_spore"s, ParticleType::WARPED_SPORE },
            { "dripping_obsidian_tear"s, ParticleType::DRIPPING_OBSIDIAN_TEAR },
            { "falling_obsidian_tear"s, ParticleType::FALLING_OBSIDIAN_TEAR },
            { "landing_obsidian_tear"s, ParticleType::LANDING_OBSIDIAN_TEAR },
            { "reverse_portal"s, ParticleType::REVERSE_PORTAL },
            { "white_ash"s, ParticleType::WHITE_ASH },
            { "redstone_dust"s, ParticleType::REDSTONE_DUST }
        };

        if (auto it = table.find(obj.to_string()); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <>
struct Json::From<SoundEvent> {
    static auto from(const SoundEvent& sound) -> Json {
        return sound.location;
    }
};

template <>
struct Json::Into<SoundEvent> {
    static auto into(const Json& obj) -> std::optional<SoundEvent> {
        return SoundEvent {
            .location = obj.to_string()
        };
    }
};

template<>
struct Json::From<ParticleEffectAmbience> {
    static auto from(const ParticleEffectAmbience &effect) -> Json {
        return {
            {"type", effect.type},
            {"probability", effect.probability}
        };
    }
};

template<>
struct Json::Into<ParticleEffectAmbience> {
    static auto into(const Json& obj) -> std::optional<ParticleEffectAmbience> {
        auto&& o = obj.to_object();
        return ParticleEffectAmbience{
            .type = o.at("type"),
            .probability = o.at("probability")
        };
    }
};

template<>
struct Json::From<MoodSoundAmbience> {
    static auto from(const MoodSoundAmbience &sound) -> Json {
        return {
            {"sound", sound.sound},
            {"delay", sound.delay},
            {"radius", sound.radius},
            {"offset", sound.offset}
        };
    }
};

template<>
struct Json::Into<MoodSoundAmbience> {
    static auto into(const Json &obj) -> std::optional<MoodSoundAmbience> {
        auto&& o = obj.to_object();
        return MoodSoundAmbience{
            .sound = o.at("sound"),
            .delay = o.at("delay"),
            .radius = o.at("radius"),
            .offset = o.at("offset")
        };
    }
};

template<>
struct Json::From<SoundAdditionsAmbience> {
    static auto from(const SoundAdditionsAmbience &sound) -> Json {
        return {
            {"sound", sound.sound},
            {"chance", sound.chance}
        };
    }
};

template<>
struct Json::Into<SoundAdditionsAmbience> {
    static auto into(const Json &obj) -> std::optional<SoundAdditionsAmbience> {
        auto&& o = obj.to_object();
        return SoundAdditionsAmbience{
            .sound = o.at("sound"),
            .chance = o.at("chance")
        };
    }
};

template<>
struct Json::From<BackgroundMusicTrack> {
    static auto from(const BackgroundMusicTrack &track) -> Json {
        return {
            { "sound", track.sound},
            { "min_delay", track.minDelay},
            { "max_delay", track.maxDelay},
            { "replace_current_music", track.replaceCurrentMusic},
        };
    }
};


template<>
struct Json::Into<BackgroundMusicTrack> {
    static auto into(const Json &obj) -> std::optional<BackgroundMusicTrack> {
        auto&& o = obj.to_object();
        return BackgroundMusicTrack{
            .sound = o.at("sound"),
            .minDelay = o.at("min_delay"),
            .maxDelay = o.at("max_delay"),
            .replaceCurrentMusic = o.at("replace_current_music")
        };
    }
};

template<>
struct Json::From<BiomeAmbience> {
    static auto from(const BiomeAmbience &ambience) -> Json {
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
struct Json::Into<BiomeAmbience> {
    static auto into(const Json& obj) -> std::optional<BiomeAmbience> {
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
            .foliageColor = foliage_color != o.end() ? std::optional(foliage_color->second) : std::nullopt,
            .grassColor = grass_color != o.end() ? std::optional(grass_color->second) : std::nullopt,
            .grassColorModifier = o.at("grass_color_modifier"),
            .particle = particle != o.end() ? std::optional(particle->second) : std::nullopt,
            .ambientSound = ambient_sound != o.end() ? std::optional(ambient_sound->second) : std::nullopt,
            .additionsSound = additions_sound != o.end() ? std::optional(additions_sound->second) : std::nullopt,
            .music = music != o.end() ? std::optional(music->second) : std::nullopt
        };
    }
};

//template<>
//struct Json::From<BiomeClimate> {
//    static auto from(const BiomeClimate &climate) -> Json {
//        return {
//            {"precipitation", climate.precipitation},
//            {"temperature", climate.temperature},
//            {"temperature_modifier", climate.temperatureModifier},
//            {"downfall", climate.downfall}
//        };
//    }
//};

//template<>
//struct Json::Into<BiomeClimate> {
//    static auto into(const Json& obj) -> std::optional<BiomeClimate> {
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
struct Json::From<SurfaceBuilder*> {
    static auto from(SurfaceBuilder* builder) -> Json {
        return SurfaceBuilders::builders.name(builder).value();
    }
};

template<>
struct Json::Into<SurfaceBuilder*> {
    static auto into(const Json& obj) -> std::optional<SurfaceBuilder*> {
        return SurfaceBuilders::builders.get(obj.to_string());
    }
};

template<>
struct Json::From<ConfiguredSurfaceBuilder*> {
    static auto from(ConfiguredSurfaceBuilder* builder) -> Json {
        return ConfiguredSurfaceBuilders::builders.name(builder).value();
    }
};

template<>
struct Json::Into<ConfiguredSurfaceBuilder*> {
    static auto into(const Json& obj) -> std::optional<ConfiguredSurfaceBuilder*> {
        return ConfiguredSurfaceBuilders::builders.get(obj.to_string());
    }
};

template<>
struct Json::From<ConfiguredFeature*> {
    static auto from(ConfiguredFeature* feature) -> Json {
        return ConfiguredFeatures::features.name(feature).value();
    }
};

template<>
struct Json::Into<ConfiguredFeature*> {
    static auto into(const Json& obj) -> std::optional<ConfiguredFeature*> {
        return ConfiguredFeatures::features.get(obj.to_string());
    }
};

template<>
struct Json::From<Structure*> {
    static auto from(Structure* structure) -> Json {
        return Structures::registry.name(structure).value();
    }
};

template<>
struct Json::Into<Structure*> {
    static auto into(const Json& obj) -> std::optional<Structure*> {
        return Structures::registry.get(obj.to_string());
    }
};

template<>
struct Json::From<StructureFeature*> {
    static auto from(StructureFeature* structure) -> Json {
        return StructureFeatures::registry.name(structure).value();
    }
};

template<>
struct Json::Into<StructureFeature*> {
    static auto into(const Json& obj) -> std::optional<StructureFeature*> {
        return StructureFeatures::registry.get(obj.to_string());
    }
};

template<>
struct Json::From<ConfiguredCarver*> {
    static auto from(ConfiguredCarver* carver) -> Json {
        return ConfiguredCarvers::carvers.name(carver).value();
    }
};

template<>
struct Json::Into<ConfiguredCarver*> {
    static auto into(const Json& obj) -> std::optional<ConfiguredCarver*> {
        return ConfiguredCarvers::carvers.get(obj.to_string());
    }
};

//template<>
//struct Json::From<BiomeGenerationSettings> {
//    static auto from(const BiomeGenerationSettings &settings) -> Json {
//        return {
//            {"surface", settings.surfaceBuilder},
//            {"carvers", settings.carvers},
//            {"features", settings.features},
//            {"structures", settings.structures}
//        };
//    }
//};

//template<>
//struct Json::Into<BiomeGenerationSettings> {
//    static auto into(const Json& obj) -> std::optional<BiomeGenerationSettings> {
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
struct Json::From<RuinedPortalConfig> {
    static auto from(const RuinedPortalConfig &config) -> Json {
        return {
            {"location", config.location},
        };
    }
};

template<>
struct Json::Into<RuinedPortalConfig> {
    static auto into(const Json &obj) -> std::optional<RuinedPortalConfig> {
        auto&& o = obj.to_object();
        return RuinedPortalConfig{
            .location = o.at("location")
        };
    }
};

template<>
struct Json::From<JigsawConfig> {
    static auto from(const JigsawConfig &config) -> Json {
        return {
            { "pool", config.pool->location },
            { "size", config.size }
        };
    }
};

template<>
struct Json::Into<JigsawConfig> {
    static auto into(const Json &obj) -> std::optional<JigsawConfig> {
        auto&& o = obj.to_object();
        return JigsawConfig{
            .pool = JigsawPools::findByName(o.at("pool").to_string()),
            .size = o.at("size")
        };
    }
};

template<>
struct Json::From<ShipwreckConfig> {
    static auto from(const ShipwreckConfig &config) -> Json {
        return {
            {"is_beached", config.isBeached}
        };
    }
};

template<>
struct Json::Into<ShipwreckConfig> {
    static auto into(const Json &obj) -> std::optional<ShipwreckConfig> {
        auto&& o = obj.to_object();
        return ShipwreckConfig{
            .isBeached = o.at("is_beached")
        };
    }
};

template<>
struct Json::From<OceanRuinConfig> {
    static auto from(const OceanRuinConfig &config) -> Json {
        return {
            {"type", config.type},
            {"large_probability", config.largeProbability},
            {"cluster_probability", config.clusterProbability}
        };
    }
};

template<>
struct Json::Into<OceanRuinConfig> {
    static auto into(const Json &obj) -> std::optional<OceanRuinConfig> {
        auto&& o = obj.to_object();
        return OceanRuinConfig{
            .type = o.at("type"),
            .largeProbability = o.at("large_probability"),
            .clusterProbability = o.at("cluster_probability")
        };
    }
};

template<>
struct Json::From<ProbabilityConfig> {
    static auto from(const ProbabilityConfig &config) -> Json {
        return {
            {"probability", config.probability}
        };
    }
};

template<>
struct Json::Into<ProbabilityConfig> {
    static auto into(const Json& obj) -> std::optional<ProbabilityConfig> {
        auto&& o = obj.to_object();
        return ProbabilityConfig{
            .probability = o.at("probability")
        };
    }
};

template<>
struct Json::From<WorldCarver*> {
    static auto from(WorldCarver* carver) -> Json {
        return Carvers::carvers.name(carver).value();
    }
};

template<>
struct Json::Into<WorldCarver*> {
    static auto into(const Json& obj) -> std::optional<WorldCarver*> {
        return Carvers::carvers.get(obj.to_string());
    }
};

template<>
struct Json::From<EntityType> {
    static auto from(const EntityType& type) -> Json {
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

template <>
struct Json::Into<EntityType> {
    static auto into(const Json& obj) -> std::optional<EntityType> {
        using namespace std::string_literals;

        static auto table = std::map<std::string, EntityType> {
            {"area_effect_cloud"s, EntityType::AREA_EFFECT_CLOUD},
            {"armor_stand"s, EntityType::ARMOR_STAND},
            {"arrow"s, EntityType::ARROW},
            {"bat"s, EntityType::BAT},
            {"bee"s, EntityType::BEE},
            {"blaze"s, EntityType::BLAZE},
            {"boat"s, EntityType::BOAT},
            {"cat"s, EntityType::CAT},
            {"cave_spider"s, EntityType::CAVE_SPIDER},
            {"chicken"s, EntityType::CHICKEN},
            {"cod"s, EntityType::COD},
            {"cow"s, EntityType::COW},
            {"creeper"s, EntityType::CREEPER},
            {"dolphin"s, EntityType::DOLPHIN},
            {"donkey"s, EntityType::DONKEY},
            {"dragon_fireball"s, EntityType::DRAGON_FIREBALL},
            {"drowned"s, EntityType::DROWNED},
            {"elder_guardian"s, EntityType::ELDER_GUARDIAN},
            {"end_crystal"s, EntityType::END_CRYSTAL},
            {"ender_dragon"s, EntityType::ENDER_DRAGON},
            {"enderman"s, EntityType::ENDERMAN},
            {"endermite"s, EntityType::ENDERMITE},
            {"evoker"s, EntityType::EVOKER},
            {"evoker_fangs"s, EntityType::EVOKER_FANGS},
            {"experience_orb"s, EntityType::EXPERIENCE_ORB},
            {"eye_of_ender"s, EntityType::EYE_OF_ENDER},
            {"falling_block"s, EntityType::FALLING_BLOCK},
            {"firework_rocket"s, EntityType::FIREWORK_ROCKET},
            {"fox"s, EntityType::FOX},
            {"ghast"s, EntityType::GHAST},
            {"giant"s, EntityType::GIANT},
            {"guardian"s, EntityType::GUARDIAN},
            {"hoglin"s, EntityType::HOGLIN},
            {"horse"s, EntityType::HORSE},
            {"husk"s, EntityType::HUSK},
            {"illusioner"s, EntityType::ILLUSIONER},
            {"iron_golem"s, EntityType::IRON_GOLEM},
            {"item"s, EntityType::ITEM},
            {"item_frame"s, EntityType::ITEM_FRAME},
            {"fireball"s, EntityType::FIREBALL},
            {"leash_knot"s, EntityType::LEASH_KNOT},
            {"lightning_bolt"s, EntityType::LIGHTNING_BOLT},
            {"llama"s, EntityType::LLAMA},
            {"llama_spit"s, EntityType::LLAMA_SPIT},
            {"magma_cube"s, EntityType::MAGMA_CUBE},
            {"minecart"s, EntityType::MINECART},
            {"chest_minecart"s, EntityType::CHEST_MINECART},
            {"command_block_minecart"s, EntityType::COMMAND_BLOCK_MINECART},
            {"furnace_minecart"s, EntityType::FURNACE_MINECART},
            {"hopper_minecart"s, EntityType::HOPPER_MINECART},
            {"spawner_minecart"s, EntityType::SPAWNER_MINECART},
            {"tnt_minecart"s, EntityType::TNT_MINECART},
            {"mule"s, EntityType::MULE},
            {"mooshroom"s, EntityType::MOOSHROOM},
            {"ocelot"s, EntityType::OCELOT},
            {"painting"s, EntityType::PAINTING},
            {"panda"s, EntityType::PANDA},
            {"parrot"s, EntityType::PARROT},
            {"phantom"s, EntityType::PHANTOM},
            {"pig"s, EntityType::PIG},
            {"piglin"s, EntityType::PIGLIN},
            {"field_242287_aj"s, EntityType::field_242287_aj},
            {"pillager"s, EntityType::PILLAGER},
            {"polar_bear"s, EntityType::POLAR_BEAR},
            {"tnt"s, EntityType::TNT},
            {"pufferfish"s, EntityType::PUFFERFISH},
            {"rabbit"s, EntityType::RABBIT},
            {"ravager"s, EntityType::RAVAGER},
            {"salmon"s, EntityType::SALMON},
            {"sheep"s, EntityType::SHEEP},
            {"shulker"s, EntityType::SHULKER},
            {"shulker_bullet"s, EntityType::SHULKER_BULLET},
            {"silverfish"s, EntityType::SILVERFISH},
            {"skeleton"s, EntityType::SKELETON},
            {"skeleton_horse"s, EntityType::SKELETON_HORSE},
            {"slime"s, EntityType::SLIME},
            {"small_fireball"s, EntityType::SMALL_FIREBALL},
            {"snow_golem"s, EntityType::SNOW_GOLEM},
            {"snowball"s, EntityType::SNOWBALL},
            {"spectral_arrow"s, EntityType::SPECTRAL_ARROW},
            {"spider"s, EntityType::SPIDER},
            {"squid"s, EntityType::SQUID},
            {"stray"s, EntityType::STRAY},
            {"strider"s, EntityType::STRIDER},
            {"egg"s, EntityType::EGG},
            {"ender_pearl"s, EntityType::ENDER_PEARL},
            {"experience_bottle"s, EntityType::EXPERIENCE_BOTTLE},
            {"potion"s, EntityType::POTION},
            {"trident"s, EntityType::TRIDENT},
            {"trader_llama"s, EntityType::TRADER_LLAMA},
            {"tropical_fish"s, EntityType::TROPICAL_FISH},
            {"turtle"s, EntityType::TURTLE},
            {"vex"s, EntityType::VEX},
            {"villager"s, EntityType::VILLAGER},
            {"vindicator"s, EntityType::VINDICATOR},
            {"wandering_trader"s, EntityType::WANDERING_TRADER},
            {"witch"s, EntityType::WITCH},
            {"wither"s, EntityType::WITHER},
            {"wither_skeleton"s, EntityType::WITHER_SKELETON},
            {"wither_skull"s, EntityType::WITHER_SKULL},
            {"wolf"s, EntityType::WOLF},
            {"zoglin"s, EntityType::ZOGLIN},
            {"zombie"s, EntityType::ZOMBIE},
            {"zombie_horse"s, EntityType::ZOMBIE_HORSE},
            {"zombie_villager"s, EntityType::ZOMBIE_VILLAGER},
            {"zombified_piglin"s, EntityType::ZOMBIFIED_PIGLIN},
            {"player"s, EntityType::PLAYER},
            {"fishing_bobber"s, EntityType::FISHING_BOBBER},
        };

        if (auto it = table.find(obj.to_string()); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template<>
struct Json::From<EntityClassification> {
    static auto from(const EntityClassification& entity) -> Json {
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

template <>
struct Json::Into<EntityClassification> {
    static auto into(const Json& obj) -> std::optional<EntityClassification> {
        using namespace std::string_literals;

        static auto table = std::map<std::string, EntityClassification> {
            {"monster"s, EntityClassification::MONSTER},
            {"creature"s, EntityClassification::CREATURE},
            {"ambient"s, EntityClassification::AMBIENT},
            {"water_creature"s, EntityClassification::WATER_CREATURE},
            {"water_ambient"s, EntityClassification::WATER_AMBIENT},
            {"misc"s, EntityClassification::MISC}
        };

        if (auto it = table.find(obj.to_string()); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template<>
struct Json::From<MobSpawnInfo::SpawnCosts> {
    static auto from(const MobSpawnInfo::SpawnCosts& costs) -> Json {
        return {
            {"maxSpawnCost", costs.maxSpawnCost},
            {"entitySpawnCost", costs.entitySpawnCost}
        };
    }
};

template<>
struct Json::Into<MobSpawnInfo::SpawnCosts> {
    static auto into(const Json& obj) -> std::optional<MobSpawnInfo::SpawnCosts> {
        auto&& o = obj.to_object();
        return MobSpawnInfo::SpawnCosts{
            .maxSpawnCost = o.at("maxSpawnCost"),
            .entitySpawnCost = o.at("entitySpawnCost")
        };
    }
};

template<>
struct Json::From<MobSpawnInfo::Spawners> {
    static auto from(const MobSpawnInfo::Spawners& spawners) -> Json {
        return {
            {"type", spawners.type},
            {"weight", spawners.weight},
            {"min_count", spawners.minCount},
            {"max_count", spawners.maxCount},
        };
    }
};

template<>
struct Json::Into<MobSpawnInfo::Spawners> {
    static auto into(const Json& obj) -> std::optional<MobSpawnInfo::Spawners> {
        auto&& o = obj.to_object();
        return MobSpawnInfo::Spawners{
            .type = o.at("type"),
            .weight = o.at("weight"),
            .minCount = o.at("min_count"),
            .maxCount = o.at("max_count")
        };
    }
};