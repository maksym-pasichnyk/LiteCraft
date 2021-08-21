#pragma once

#include <block/BlockData.hpp>
#include <world/gen/feature/FeatureSpread.hpp>

struct BlobReplacementConfig {
    BlockData target;
    BlockData state;
    FeatureSpread radius;
};