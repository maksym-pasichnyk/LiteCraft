#pragma once

#include "Feature.hpp"

struct CoralFeature : Feature {
    bool generate(WorldGenRegion& reader, ChunkGenerator& generator, Random& random, BlockPos pos, const FeatureConfig& config) override;
    bool generateCorals(WorldGenRegion& reader, Random& random, const BlockPos& pos, BlockData state);

    virtual bool generate(WorldGenRegion& reader, Random& random, const BlockPos& pos, BlockData state) = 0;
};