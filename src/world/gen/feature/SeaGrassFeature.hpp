#pragma once

#include "Feature.hpp"

struct SeaGrassFeature : Feature {
    bool generate(WorldGenRegion& reader, ChunkGenerator& generator, Random& random, BlockPos pos, const FeatureConfig& config) override;
};