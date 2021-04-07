#pragma once

#include "../../../../block/BlockData.hpp"

#include <set>

struct BlockWithContextConfig {
    BlockData toPlace;
    std::set<BlockData> placeOn;
    std::set<BlockData> placeIn;
    std::set<BlockData> placeUnder;
};