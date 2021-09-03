#pragma once

#include <json/json.hpp>

#include <world/biome/BiomeClimate.hpp>
#include <world/biome/BiomeCategory.hpp>
#include <world/biome/BiomeAmbience.hpp>
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
struct Json::Serialize<BiomeAmbience> {
    static auto to_json(const BiomeAmbience &ambience) -> Json {
        return {
            {"fog_color", ambience.fogColor},
            {"water_color", ambience.waterColor},
            {"water_fog_color", ambience.waterFogColor},
            {"sky_color", ambience.skyColor},
//            {"foliageColor", ambience.foliageColor},
//            {"grassColor", ambience.grassColor},
        };
    }
};

template<>
struct Json::Deserialize<BiomeAmbience> {
    static auto from_json(const Json& obj) -> std::optional<BiomeAmbience> {
        auto&& o = obj.to_object();
        return BiomeAmbience{
            .fogColor = o.at("fog_color"),
            .waterColor = o.at("water_color"),
            .waterFogColor = o.at("water_fog_color"),
            .skyColor = o.at("sky_color")
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
struct Json::Serialize<ProbabilityConfig> {
    static auto to_json(const ProbabilityConfig &config) -> Json {
        return {
            {"probability", config.probability},
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