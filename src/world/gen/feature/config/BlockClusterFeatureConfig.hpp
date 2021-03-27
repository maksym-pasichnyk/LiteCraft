#pragma once

#include "../../../../block/BlockData.hpp"

#include <set>

struct Block;
struct BlockPlacer;
struct BlockStateProvider;
struct BlockClusterFeatureConfig {
    std::set<Block*> whitelist{};
    std::set<BlockData> blacklist{};

    BlockStateProvider* stateProvider = nullptr;
    BlockPlacer* blockPlacer = nullptr;
    int tries = 128;
    int xspread = 7;
    int yspread = 3;
    int zspread = 7;
    bool can_replace = false;
    bool project = true;
    bool requiresWater = false;
};