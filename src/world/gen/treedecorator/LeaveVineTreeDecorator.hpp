#pragma once

#include "TreeDecorator.hpp"

struct LeaveVineTreeDecorator : TreeDecorator {
    static void placeVines(WorldGenRegion& reader, const BlockPos& pos/*, BooleanProperty p_227420_3_*/, std::set<BlockPos>& p_227420_4_, BoundingBox& boundingBox);

    void decorate(WorldGenRegion &reader, Random &random, std::vector<BlockPos> &positions1, std::vector<BlockPos> &positions2, std::set<BlockPos> &positions3, BoundingBox &boundingBox) override;
};