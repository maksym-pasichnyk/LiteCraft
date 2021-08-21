#pragma once

#include "CoralFeature.hpp"

struct CoralClawFeature : CoralFeature {
    bool generate(WorldGenRegion& reader, Random& random, const BlockPos& pos, BlockData state) override;
};