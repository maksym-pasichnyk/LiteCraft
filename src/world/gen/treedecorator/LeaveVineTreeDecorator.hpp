#pragma once

#include "TreeDecorator.hpp"

struct LeaveVineTreeDecorator : TreeDecorator {
    static void placeVines(WorldGenRegion& reader, const BlockPos& pos, BlockStateProperty property, std::set<BlockPos>& positions, BoundingBox& boundingBox);

    void decorate(WorldGenRegion &reader, Random &random, std::vector<BlockPos> &positions1, std::vector<BlockPos> &positions2, std::set<BlockPos> &positions3, BoundingBox &boundingBox) override;
};