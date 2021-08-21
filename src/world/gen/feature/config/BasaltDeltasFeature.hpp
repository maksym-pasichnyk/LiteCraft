#pragma once

#include <block/BlockData.hpp>
#include <world/gen/feature/FeatureSpread.hpp>

struct BasaltDeltasFeature {
    BlockData contents;
    BlockData rim;
    FeatureSpread size;
    FeatureSpread rim_size;
};