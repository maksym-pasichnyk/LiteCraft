#pragma once

#include "Feature.hpp"

struct NetherackBlobReplacementStructure : Feature {
    bool generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) override;
    
    static auto getLowestPosition(WorldGenRegion &reader, const BlockPos& start, Block* block) -> tl::optional<BlockPos>;
};