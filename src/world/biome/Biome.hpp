#pragma once

#include "BiomeGenerationSettings.hpp"
#include "BiomeAmbience.hpp"
#include "BiomeClimate.hpp"
#include "BiomeCategory.hpp"

#include "../gen/PerlinNoiseGenerator.hpp"
#include "../../block/BlockData.hpp"
#include "../../util/math/BlockPos.hpp"
#include "../../util/linked_unordered_map.hpp"

#include <glm/vec3.hpp>
#include <string_view>
#include <functional>
#include <variant>
#include <memory>
#include <map>

struct ChunkGenerator;
struct WorldGenRegion;
struct WorldReader;
struct Random;
struct Chunk;

struct Biome {
    static const PerlinNoiseGenerator TEMPERATURE_NOISE;
    static const PerlinNoiseGenerator FROZEN_TEMPERATURE_NOISE;
    static const PerlinNoiseGenerator INFO_NOISE;

    BiomeClimate climate;
    BiomeGenerationSettings biomeGenerationSettings;
//    MobSpawnInfo mobSpawnInfo;
    float depth;
    float scale;
    BiomeCategory category;
    BiomeAmbience effects;

    linked_unordered_map<uint64_t, float> temperatureCache{};

    float getDepth() const {
        return depth;
    }

    float getScale() const {
        return scale;
    }

    auto getSkyColor() const -> int32_t {
        return effects.skyColor;
    }

    auto getTemperature() const -> float {
        return climate.temperature;
    }

    float getTemperatureAtPosition(BlockPos pos) const {
        const float f = climate.temperatureModifier(pos, climate.temperature);
        if (pos.y > 64) {
            const auto f1 = static_cast<float>(TEMPERATURE_NOISE.noiseAt(
                    static_cast<float>(pos.x) / 8.0F,
                    static_cast<float>(pos.z) / 8.0F,
                    false) * 4.0);
            return f - (f1 + static_cast<float>(pos.y) - 64.0F) * 0.05F / 30.0F;
        }
        return f;
    }

    float getTemperature(BlockPos pos) /*const*/ {
        const auto i = BlockPos::pack(pos.x, pos.y, pos.z);
        if (temperatureCache.contains(i)) {
            return temperatureCache.at(i);
        }

        const auto f = getTemperatureAtPosition(pos);
        if (temperatureCache.size() >= 1024) {
            temperatureCache.pop_front();
        }

        temperatureCache.insert({i, f});
        return f;
    }

    BiomeGenerationSettings& getGenerationSettings() {
        return biomeGenerationSettings;
    }

    void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int sealevel, int64_t worldSeed) {
        biomeGenerationSettings.surfaceBuilder.setSeed(worldSeed);
        biomeGenerationSettings.surfaceBuilder.buildSurface(rand, chunk, *this, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, sealevel);
    }

    void decorate(ChunkGenerator& generator, WorldGenRegion& region, int64_t seed, Random& random, BlockPos pos);

    bool doesWaterFreeze(WorldReader& world, const BlockPos& pos, bool mustBeAtEdge = true);
    bool doesSnowGenerate(WorldReader& world, const BlockPos& pos);
};