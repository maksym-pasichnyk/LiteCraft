#pragma once

#include "TreeDecorator.hpp"

struct BeehiveTreeDecorator : TreeDecorator {
    float probability;
    explicit BeehiveTreeDecorator(float probability) : probability(probability) {}

    void decorate(WorldGenRegion &reader, Random &random, std::vector<BlockPos> &positions1, std::vector<BlockPos> &positions2, std::set<BlockPos> &positions3, BoundingBox &boundingBox) override;
};