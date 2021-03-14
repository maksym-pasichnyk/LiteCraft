#pragma once

#include "../../SurfaceBuilder.h"
#include "../../block/BlockTable.hpp"
#include "../../block/BlockData.hpp"
#include "../../util/Random.hpp"
#include "../../resource_manager.hpp"
#include "../gen/PerlinNoiseGenerator.hpp"
#include "../gen/surface/SurfaceBuilder.hpp"

#include <glm/vec3.hpp>
#include <functional>
#include <variant>
#include <memory>
#include <map>

struct Chunk;
struct ResourcePackManager;

//struct BiomeDefinition {
//    static std::map<std::string, std::unique_ptr<Biome>> biomes;
//    static std::map<std::string, int> biomeIds;
//
//    static void loadMetaFile();
//    static void registerBiomes();
//};

struct Biome {
    static std::map<int, std::unique_ptr<Biome>> biomes;

    static Biome* OCEAN;
    static Biome* PLAINS;
    static Biome* DESERT;
    static Biome* MOUNTAINS;
    static Biome* FOREST;
    static Biome* TAIGA;
    static Biome* SWAMP;
    static Biome* RIVER;
    static Biome* NETHER_WASTES;
    static Biome* THE_END;
    static Biome* FROZEN_OCEAN;
    static Biome* FROZEN_RIVER;
    static Biome* SNOWY_TUNDRA;
    static Biome* SNOWY_MOUNTAINS;
    static Biome* MUSHROOM_FIELDS;
    static Biome* MUSHROOM_FIELD_SHORE;
    static Biome* BEACH;
    static Biome* DESERT_HILLS;
    static Biome* WOODED_HILLS;
    static Biome* TAIGA_HILLS;
    static Biome* MOUNTAIN_EDGE;
    static Biome* JUNGLE;
    static Biome* JUNGLE_HILLS;
    static Biome* JUNGLE_EDGE;
    static Biome* DEEP_OCEAN;
    static Biome* STONE_SHORE;
    static Biome* SNOWY_BEACH;
    static Biome* BIRCH_FOREST;
    static Biome* BIRCH_FOREST_HILLS;
    static Biome* DARK_FOREST;
    static Biome* SNOWY_TAIGA;
    static Biome* SNOWY_TAIGA_HILLS;
    static Biome* GIANT_TREE_TAIGA;
    static Biome* GIANT_TREE_TAIGA_HILLS;
    static Biome* WOODED_MOUNTAINS;
    static Biome* SAVANNA;
    static Biome* SAVANNA_PLATEAU;
    static Biome* BADLANDS;
    static Biome* WOODED_BADLANDS_PLATEAU;
    static Biome* BADLANDS_PLATEAU;
    static Biome* SMALL_END_ISLANDS;
    static Biome* END_MIDLANDS;
    static Biome* END_HIGHLANDS;
    static Biome* END_BARRENS;
    static Biome* WARM_OCEAN;
    static Biome* LUKEWARM_OCEAN;
    static Biome* COLD_OCEAN;
    static Biome* DEEP_WARM_OCEAN;
    static Biome* DEEP_LUKEWARM_OCEAN;
    static Biome* DEEP_COLD_OCEAN;
    static Biome* DEEP_FROZEN_OCEAN;
    static Biome* THE_VOID;
    static Biome* SUNFLOWER_PLAINS;
    static Biome* DESERT_LAKES;
    static Biome* GRAVELLY_MOUNTAINS;
    static Biome* FLOWER_FOREST;
    static Biome* TAIGA_MOUNTAINS;
    static Biome* SWAMP_HILLS;
    static Biome* ICE_SPIKES;
    static Biome* MODIFIED_JUNGLE;
    static Biome* MODIFIED_JUNGLE_EDGE;
    static Biome* TALL_BIRCH_FOREST;
    static Biome* TALL_BIRCH_HILLS;
    static Biome* DARK_FOREST_HILLS;
    static Biome* SNOWY_TAIGA_MOUNTAINS;
    static Biome* GIANT_SPRUCE_TAIGA;
    static Biome* GIANT_SPRUCE_TAIGA_HILLS;
    static Biome* MODIFIED_GRAVELLY_MOUNTAINS;
    static Biome* SHATTERED_SAVANNA;
    static Biome* SHATTERED_SAVANNA_PLATEAU;
    static Biome* ERODED_BADLANDS;
    static Biome* MODIFIED_WOODED_BADLANDS_PLATEAU;
    static Biome* MODIFIED_BADLANDS_PLATEAU;
    static Biome* BAMBOO_JUNGLE;
    static Biome* BAMBOO_JUNGLE_HILLS;
    static Biome* SOUL_SAND_VALLEY;
    static Biome* CRIMSON_FOREST;
    static Biome* WARPED_FOREST;
    static Biome* BASALT_DELTAS;

//    static PerlinNoiseGenerator TEMPERATURE_NOISE;
//    static PerlinNoiseGenerator FROZEN_TEMPERATURE_NOISE;
    inline static const PerlinNoiseGenerator INFO_NOISE = PerlinNoiseGenerator(Random::from(2345), 0, 0);


//    struct TemperatureModifier {
//        TemperatureModifier() : TemperatureModifier(none()) {}
//
//        static constexpr auto none() -> TemperatureModifier {
//            return TemperatureModifier{[](glm::ivec3 pos, float temperature) -> float {
//                    return temperature;
//            }};
//        }
//
//        static constexpr auto frozen() -> TemperatureModifier {
//            return TemperatureModifier{[](glm::ivec3 pos, float temperature) -> float {
//                const double frozen = Biome::FROZEN_TEMPERATURE_NOISE.noiseAt(
//                        static_cast<double>(pos.x) * 0.05,
//                        static_cast<double>(pos.z) * 0.05,
//                        false) * 7.0;
//
//                const double noise = Biome::INFO_NOISE.noiseAt(
//                        static_cast<double>(pos.x) * 0.2,
//                        static_cast<double>(pos.z) * 0.2,
//                        false);
//
//                if ((frozen + noise) < 0.3) {
//                    const double d3 = Biome::INFO_NOISE.noiseAt(
//                            static_cast<double>(pos.x) * 0.09,
//                            static_cast<double>(pos.z) * 0.09,
//                            false);
//
//                    if (d3 < 0.8) {
//                        return 0.2F;
//                    }
//                }
//                return temperature;
//            }};
//        }
//
//        float getTemperatureAtPosition(glm::ivec3 pos, float temperature) const {
//            return _getTemperatureAtPosition(pos, temperature);
//        }
//    private:
//        constexpr TemperatureModifier(float(*_getTemperatureAtPosition)(glm::ivec3, float)) : _getTemperatureAtPosition(_getTemperatureAtPosition) {}
//
//        float(*_getTemperatureAtPosition)(glm::ivec3, float);
//    };

    struct Attributes {
        float temperature;
        float humidity;
        float altitude;
        float weirdness;
        float offset;

        float getAttributeDifference(const Attributes& attributes) const {
            return (temperature - attributes.temperature) * (temperature - attributes.temperature)
                + (humidity - attributes.humidity) * (humidity - attributes.humidity)
                + (altitude - attributes.altitude) * (altitude - attributes.altitude)
                + (weirdness - attributes.weirdness) * (weirdness - attributes.weirdness)
                + (offset - attributes.offset) * (offset - attributes.offset);
        }
    };
//
//    enum class RainType {
//        none,
//        rain,
//        snow
//    };
//
//    enum class Category {
//        none,
//        taiga,
//        extreme_hills,
//        jungle,
//        mesa,
//        plains,
//        savanna,
//        icy,
//        the_end,
//        beach,
//        forest,
//        ocean,
//        desert,
//        river,
//        swamp,
//        mushroom,
//        nether
//    };
//
//    struct Climate {
//        RainType precipitation;
//        float temperature;
//        TemperatureModifier temperatureModifier;
//        float downfall;
//    };

    Biome(float depth, float scale, ConfiguredSurfaceBuilder builder) : depth(depth), scale(scale), builder(builder) {}

    float getDepth() const {
        return depth.value();
    }

    float getScale() const {
        return scale.value();
    }
//    auto getSkyColor() const -> int32_t {
//        return 0xFFFFFFFF;
//    }
//
//    auto getTemperature() const -> float {
//        return 0;
//    }

//    float getTemperatureAtPosition(glm::ivec3 pos) const {
//        const auto temp = climate.temperatureModifier.getTemperatureAtPosition(pos, getTemperature());
//
////        return temperatureModifier.getTemperatureAtPosition(pos, temperature);
//    }

    void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int sealevel) {
        builder.setSeed(0);
        builder.buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, sealevel);
    }

    static Biome* registerBiome(int id, Biome* biome);
    static void registerBiomes();

//private:
    ConfiguredSurfaceBuilder builder;

//    std::optional<BlockData> top;
//    std::optional<BlockData> filler;
//    std::optional<BlockData> underWater;
    //    SurfaceBuilder surfaceBuilder;
//    Climate climate;
//    BiomeGenerationSettings generationSettings;
    std::optional<float> depth;
    std::optional<float> scale;
    std::optional<float> temperature;
//    Category category;
//    BiomeAmbience effects;
};