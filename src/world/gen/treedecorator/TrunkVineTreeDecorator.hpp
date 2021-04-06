#pragma once

#include "TreeDecorator.hpp"

struct TrunkVineTreeDecorator : TreeDecorator {
    void decorate(WorldGenRegion &reader, Random &random, std::vector<BlockPos> &positions1, std::vector<BlockPos> &positions2, std::set<BlockPos> &positions3, BoundingBox &boundingBox) override;
};