#pragma once

#include "config/FeatureConfig.hpp"

#include <glm/vec3.hpp>

struct Random;
struct Feature;
struct WorldGenRegion;
struct ChunkGenerator;
struct ConfiguredFeature {
    Feature* feature;
    FeatureConfig config;

    void generate(WorldGenRegion &region, ChunkGenerator &generator, Random &random, glm::ivec3 vec);
};