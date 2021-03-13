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

//    struct Attributes {
//        float temperature;
//        float humidity;
//        float altitude;
//        float weirdness;
//        float offset;
//    };
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

    Biome(float depth, float scale, SurfaceBuilder* builder) : depth(depth), scale(scale), builder(builder) {
        top = {Block::grass->id, 0};
        filler = {Block::stone->id, 0};
        underWater = {Block::gravel->id, 0};
    }

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
        builder->setSeed(0);
        builder->buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top.value(), filler.value(), underWater.value(), sealevel);
    }

    static void registerBiome(int id, Biome* biome);
    static void registerBiomes();

//private:
    SurfaceBuilder* builder;

    std::optional<BlockData> top;
    std::optional<BlockData> filler;
    std::optional<BlockData> underWater;
    //    SurfaceBuilder surfaceBuilder;
//    Climate climate;
//    BiomeGenerationSettings generationSettings;
    std::optional<float> depth;
    std::optional<float> scale;
    std::optional<float> temperature;
//    Category category;
//    BiomeAmbience effects;
};