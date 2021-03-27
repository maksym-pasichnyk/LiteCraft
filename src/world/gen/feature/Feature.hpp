#pragma once

#include "ConfiguredFeature.hpp"

#include <glm/vec3.hpp>

struct Random;
struct WorldGenRegion;
struct ChunkGenerator;

struct Feature {
    virtual ~Feature() = default;
    virtual void generate(WorldGenRegion& reader, ChunkGenerator& generator, Random& rand, glm::ivec3 pos, const FeatureConfig& config) = 0;

    auto withConfiguration(FeatureConfig config) -> ConfiguredFeature* {
        return new ConfiguredFeature {
            .feature = this,
            .config = std::move(config)
        };
    }
};