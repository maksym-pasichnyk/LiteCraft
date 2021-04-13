#pragma once

#include "../FeatureSpread.hpp"
#include "../../../../block/BlockData.hpp"

#include <vector>

struct SphereReplaceConfig {
    BlockData state;
    FeatureSpread radius;
    int half_height;
    std::vector<BlockData> targets;
};