#pragma once

#include "ConfiguredPlacement.hpp"
#include "config/PlacementConfig.hpp"

#include <functional>
#include <glm/vec3.hpp>

struct Random;
struct WorldGenRegion;
struct Placement {
    virtual void forEach(WorldGenRegion& region, Random& random, const PlacementConfig& config, BlockPos pos, const std::function<void(BlockPos)>& fn) = 0;

    ConfiguredPlacement* withConfiguration(PlacementConfig config) {
        return new ConfiguredPlacement{this, std::move(config)};
    }
};