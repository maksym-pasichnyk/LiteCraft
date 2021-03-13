#pragma once

#include "../../../WorldGenRegion.hpp"
#include "../../../util/Random.hpp"

struct BlockPlacer {
    virtual void place(WorldGenRegion& world, glm::ivec3 pos, BlockData blockData, Random& rand) = 0;
};