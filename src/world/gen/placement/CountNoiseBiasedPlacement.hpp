#pragma once

#include "Placement.hpp"

struct CountNoiseBiasedPlacement : Placement {
    void forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, glm::ivec3 pos, const std::function<void(glm::ivec3)> &fn) override;
};