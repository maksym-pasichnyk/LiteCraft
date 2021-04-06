#pragma once

#include "../../../block/BlockData.hpp"
#include "../../../util/Random.hpp"

#include "../foliageplacer/FoliagePlacer.hpp"

#include <set>
#include <list>
#include <glm/vec3.hpp>

struct Random;
struct WorldReader;
struct WorldWriter;
struct BoundingBox;
struct WorldGenRegion;
struct BaseTreeFeatureConfig;
struct AbstractTrunkPlacer {
    static bool isDirt(WorldReader& baseReader, const BlockPos& pos);
    static void placeDirt(WorldGenRegion& reader, const BlockPos& blockPos);
    static void placeBlockState(WorldWriter& reader, const BlockPos& blockPos, BlockData state, BoundingBox& boundingBox);
    static bool placeTrunk(WorldGenRegion& reader, Random& random, const BlockPos& pos, std::set<BlockPos>& set1, BoundingBox& boundingBox, const BaseTreeFeatureConfig& config);
    static void tryPlaceTrunk(WorldGenRegion& reader, Random& random, const BlockPos& pos, std::set<BlockPos>& set1, BoundingBox& boundingBox, const BaseTreeFeatureConfig& config);
    
    int base_height;
    int height_rand_a;
    int height_rand_b;

    AbstractTrunkPlacer(int base_height, int height_rand_a, int height_rand_b)
        : base_height(base_height)
        , height_rand_a(height_rand_a)
        , height_rand_b(height_rand_b) {}

    int getRandomHeight(Random& random) {
        return base_height + random.nextInt(height_rand_a + 1) + random.nextInt(height_rand_b + 1);
    }

    virtual std::list<FoliagePlacer::Foliage> getFoliages(WorldGenRegion& reader, Random& random, int heightIn, const BlockPos& blockPosIn, std::set<BlockPos>& set1, BoundingBox& boundingBox, const BaseTreeFeatureConfig& config) = 0;
};