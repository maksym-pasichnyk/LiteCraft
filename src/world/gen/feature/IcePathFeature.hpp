#pragma once

#include "AbstractSphereReplaceFeature.hpp"

struct IcePathFeature : AbstractSphereReplaceFeature {
    bool generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) override;
};