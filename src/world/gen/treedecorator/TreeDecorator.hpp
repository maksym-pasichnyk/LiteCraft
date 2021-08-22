#pragma once

#include "../../../block/BlockData.hpp"

#include "TreeDecoratorConfig.hpp"

#include <set>
#include <vector>

struct Random;
struct BoundingBox;
struct WorldWriter;
struct WorldGenRegion;

struct TreeDecorator {
    virtual ~TreeDecorator() = default;

    virtual void decorate(WorldGenRegion &reader, Random &random, std::vector<BlockPos> &positions1, std::vector<BlockPos> &positions2, std::set<BlockPos> &positions3, BoundingBox &boundingBox) = 0;

    static void placeBlock(WorldWriter& writer, const BlockPos& pos, BlockData state, std::set<BlockPos>& positions, BoundingBox& boundingBox);
    static void placeVine(WorldWriter& writer, const BlockPos& pos, BlockStateProperty property, std::set<BlockPos>& positions, BoundingBox& boundingBox);
};