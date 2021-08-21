#pragma once

#include "Feature.hpp"

struct TwistingVineFeature : Feature {
    bool generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) override;

    static bool canGenerateVines(WorldGenRegion &reader, const BlockPos& pos);
    static bool tryGenerateVines(WorldGenRegion &reader, Random& random, const BlockPos& pos, int xz_range, int y_range, int max_height);
    static void generateVines(WorldGenRegion &reader, Random& random, const BlockPos& pos, int xz_range, int y_range, int max_height);
    static auto getLowestPosition(WorldGenRegion &reader, const BlockPos& pos) -> std::optional<BlockPos>;
    static void placeVines(WorldGenRegion &reader, Random& random, const BlockPos& pos, int height, int min_age, int max_age);
};