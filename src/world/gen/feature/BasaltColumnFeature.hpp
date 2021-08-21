#pragma once

#include "Feature.hpp"
#include <set>

struct BasaltColumnFeature : Feature {
    static std::set<Block*> blacklist;

    BasaltColumnFeature();

    bool generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) override;
    bool func_236248_a_(WorldGenRegion &reader, int p_236248_2_, const BlockPos& pos, int p_236248_4_, int p_236248_5_);

    static auto func_236246_a_(WorldGenRegion &reader, int p_236246_1_, const BlockPos& pos, int p_236246_3_) -> std::optional<BlockPos>;
    static auto func_236249_a_(WorldGenRegion &reader, const BlockPos& pos, int p_236249_2_) -> std::optional<BlockPos>;
    static bool func_242762_a(WorldGenRegion &reader, int p_242762_1_, const BlockPos& pos);
    static bool func_236247_a_(WorldGenRegion &reader, int p_236247_1_, const BlockPos& pos);
};