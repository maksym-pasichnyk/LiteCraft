#pragma once

#include "BiomeGenerationSettings.hpp"
#include "MobSpawnInfo.hpp"
#include "BiomeClimate.hpp"
#include "BiomeCategory.hpp"
#include "BiomeAmbience.hpp"

#include "../gen/PerlinNoiseGenerator.hpp"
#include "../../block/BlockData.hpp"
#include "../../util/math/BlockPos.hpp"
#include "../../util/linked_unordered_map.hpp"

#include "ThreadLocal.hpp"

#include <glm/vec3.hpp>
#include <string_view>
#include <functional>
#include <variant>
#include <memory>
#include <map>

struct ChunkGenerator;
struct TemplateManager;
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
    MobSpawnInfo mobSpawnInfo;
    float depth;
    float scale;
    BiomeCategory category;
    BiomeAmbience effects;

    ThreadLocal<linked_unordered_map<uint64_t, float>> temperatureCache{};

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

    auto getTemperatureAtPosition(BlockPos pos) const -> float {
        const auto f = climate.temperatureModifier(pos, climate.temperature);
        if (pos.y > 64) {
            const auto f1 = static_cast<float>(TEMPERATURE_NOISE.noiseAt(
                    static_cast<float>(pos.x) / 8.0F,
                    static_cast<float>(pos.z) / 8.0F,
                    false) * 4.0);
            return f - (f1 + static_cast<float>(pos.y) - 64.0F) * 0.05F / 30.0F;
        }
        return f;
    }

    auto getTemperature(BlockPos pos) const -> float {
        if (!temperatureCache.has_value()) {
            temperatureCache.set(new linked_unordered_map<uint64_t, float>());
        }

        const auto i = BlockPos::pack(pos.x, pos.y, pos.z);

        auto& cache = *temperatureCache.get();

        if (cache.contains(i)) {
            return cache.at(i);
        }

        const auto f = getTemperatureAtPosition(pos);

        if (cache.size() >= 1024) {
            cache.pop_front();
        }
        cache.insert({i, f});
        return f;
    }

    auto getGenerationSettings() -> BiomeGenerationSettings& {
        return biomeGenerationSettings;
    }

    void buildSurface(SurfaceBuilderContext& ctx, int64_t seed) {
        biomeGenerationSettings.surfaceBuilder->setSeed(seed);
        biomeGenerationSettings.surfaceBuilder->buildSurface(ctx);
    }

    void decorate(ChunkGenerator& generator, WorldGenRegion& region, TemplateManager& templates, int64_t seed, const BlockPos& pos);

    bool doesWaterFreeze(WorldReader& world, const BlockPos& pos, bool mustBeAtEdge = true);
    bool doesSnowGenerate(WorldReader& world, const BlockPos& pos);
};