#pragma once

#include "TreeDecorator.hpp"

struct BlockStateProvider;
struct AlterGroundTreeDecorator : TreeDecorator {
    BlockStateProvider* provider;
    explicit AlterGroundTreeDecorator(BlockStateProvider* provider) : provider(provider) {}

    void decorate(WorldGenRegion& reader, Random &random, std::vector<BlockPos> &positions1, std::vector<BlockPos> &positions2, std::set<BlockPos> &positions3, BoundingBox &boundingBox) override;

    void placeColumn(WorldGenRegion& reader, Random &random, const BlockPos& pos);
    void placeBlocks(WorldGenRegion & reader, Random &random, const BlockPos& pos);
};