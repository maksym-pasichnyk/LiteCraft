#pragma once

#include "Feature.hpp"

#include <set>
#include <list>

struct WorldReader;
struct WorldWriter;
struct BoundingBox;
struct TreeFeature : Feature {
    static bool isVineAt(WorldReader& reader, const glm::ivec3& pos);
    static bool isWaterAt(WorldReader& reader, const glm::ivec3& pos);
    static bool isTallPlantAt(WorldReader& reader, const glm::ivec3& pos);
    static bool isAirOrLeavesAt(WorldReader& reader, const glm::ivec3& pos);
    static bool isReplaceableAt(WorldReader& reader, const glm::ivec3& pos);
    static bool isDirtOrFarmlandAt(WorldReader& reader, const glm::ivec3& pos);
    static bool isReplaceableOrLogAt(WorldReader& reader, const glm::ivec3& pos);
    static void placeBlockState(WorldWriter &writer, const glm::ivec3& pos, BlockData state);

    bool generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, glm::ivec3 pos, const FeatureConfig &config) override;
    bool place(WorldGenRegion& reader, Random& random, const glm::ivec3& pos, std::set<glm::ivec3>& set1, std::set<glm::ivec3>& set2, BoundingBox& boundingBoxIn, const BaseTreeFeatureConfig& config);
    int func_241521_a_(WorldGenRegion & reader, int p_241521_2_, const glm::ivec3& pos, const BaseTreeFeatureConfig& config);
};