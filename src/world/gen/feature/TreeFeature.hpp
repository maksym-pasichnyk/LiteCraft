#pragma once

#include "Feature.hpp"

#include <set>
#include <list>

struct WorldReader;
struct WorldWriter;
struct BoundingBox;
struct TreeFeature : Feature {
    static bool isVineAt(WorldReader& reader, const BlockPos& pos);
    static bool isWaterAt(WorldReader& reader, const BlockPos& pos);
    static bool isTallPlantAt(WorldReader& reader, const BlockPos& pos);
    static bool isAirOrLeavesAt(WorldReader& reader, const BlockPos& pos);
    static bool isReplaceableAt(WorldReader& reader, const BlockPos& pos);
    static bool isDirtOrFarmlandAt(WorldReader& reader, const BlockPos& pos);
    static bool isReplaceableOrLogAt(WorldReader& reader, const BlockPos& pos);
    static void placeBlockState(WorldWriter &writer, const BlockPos& pos, BlockData state);

    bool generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) override;
    bool place(WorldGenRegion& reader, Random& random, const BlockPos& pos, std::set<BlockPos>& set1, std::set<BlockPos>& set2, BoundingBox& boundingBoxIn, const BaseTreeFeatureConfig& config);
    int func_241521_a_(WorldGenRegion & reader, int p_241521_2_, const BlockPos& pos, const BaseTreeFeatureConfig& config);
};