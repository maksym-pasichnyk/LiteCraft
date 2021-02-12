#pragma once

#include "src/SurfaceBuilder.h"
#include "src/BlockTable.hpp"
#include "src/util/Random.hpp"
#include "src/world/gen/PerlinNoiseGenerator.hpp"

#include <glm/vec3.hpp>
#include <functional>
#include <variant>
#include <memory>

struct Chunk;

using SurfaceBuilder = void (*)(BlockTable& pallete, Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel);

struct Biome {
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

    Biome(float depth, float scale, SurfaceBuilder builder) : depth(depth), scale(scale), builder(builder) {}

    float getDepth() const {
        return depth;
    }

    float getScale() const {
        return scale;
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

    void buildSurface(BlockTable& pallete, Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int sealevel) {
        top = {pallete.getId("grass")};
        filler = {pallete.getId("stone")};
        underWater = {pallete.getId("gravel")};
        builder(pallete, rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top, filler, underWater, sealevel);
    }

private:
    SurfaceBuilder builder;

    BlockData top;
    BlockData filler;
    BlockData underWater;
    //    SurfaceBuilder surfaceBuilder;
//    Climate climate;
//    BiomeGenerationSettings generationSettings;
    float depth;
    float scale;
//    Category category;
//    BiomeAmbience effects;
};