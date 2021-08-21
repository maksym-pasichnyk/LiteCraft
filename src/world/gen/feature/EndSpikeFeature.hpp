#pragma once

#include "Feature.hpp"

struct EndSpikeFeature : Feature {
    bool generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) override;
    
    void placeSpike(WorldGenRegion &reader, Random& random, const EndSpikeFeatureConfig& config, const EndSpike& spike);
};