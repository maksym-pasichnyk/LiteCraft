#pragma once

#include "CoralFeature.hpp"

struct CoralTreeFeature : CoralFeature {
    bool generate(WorldGenRegion& reader, Random& random, const BlockPos& pos, BlockData state) override;
};