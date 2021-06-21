#pragma once

#include "block/BlockData.hpp"

#include <set>

struct LiquidsConfig {
    BlockData state;
    bool needsBlockBelow;
    int rockAmount;
    int holeAmount;
    std::set<Block*> acceptedBlocks;
};