#pragma once

#include "src/world/gen/placement/config/PlacementConfig.hpp"

#include <functional>
#include <glm/vec3.hpp>

struct Random;
struct Placement;
struct WorldGenRegion;
struct ConfiguredFeature;
struct ConfiguredPlacement {
    Placement* placement;
    PlacementConfig config;

    void forEach(WorldGenRegion& region, Random& random, glm::ivec3 pos, const std::function<void(glm::ivec3)>& fn);

    ConfiguredPlacement* withPlacement(ConfiguredPlacement* placement);
    ConfiguredPlacement* chance(int chance);
    ConfiguredPlacement* range(int maximum);
    ConfiguredPlacement* square();
    ConfiguredPlacement* withSpreadPlacement(FeatureSpread spread);

    ConfiguredPlacement* withSpreadPlacement(int base) {
        return withSpreadPlacement(FeatureSpread{base, 0});
    }

    ConfiguredPlacement* func_242732_c(int spread) {
        return withSpreadPlacement(FeatureSpread{0, spread});
    }
};