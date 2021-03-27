#pragma once

#include "config/FeatureConfig.hpp"
#include "FeatureSpread.hpp"

#include <glm/vec3.hpp>

struct Random;
struct Feature;
struct WorldGenRegion;
struct ChunkGenerator;
struct ConfiguredPlacement;
struct ConfiguredFeature {
    Feature* feature;
    FeatureConfig config;

    bool generate(WorldGenRegion &region, ChunkGenerator &generator, Random &random, glm::ivec3 vec);

    ConfiguredFeature* withPlacement(ConfiguredPlacement* placement);

    ConfiguredFeature* chance(int chance);

    ConfiguredFeature* range(int maximum);

    ConfiguredFeature* square();

    ConfiguredFeature* withSpreadPlacement(FeatureSpread spread);

    ConfiguredFeature* withSpreadPlacement(int base) {
        return withSpreadPlacement(FeatureSpread{base, 0});
    }

    ConfiguredFeature* func_242732_c(int spread) {
        return withSpreadPlacement(FeatureSpread{0, spread});
    }
};