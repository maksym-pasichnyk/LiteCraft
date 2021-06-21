#pragma once

#include "AbstractSphereReplaceFeature.hpp"

struct SphereReplaceFeature : AbstractSphereReplaceFeature {
    bool generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) override;
};