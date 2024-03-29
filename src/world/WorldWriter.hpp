#pragma once

#include "../block/BlockData.hpp"

struct WorldWriter {
    virtual bool setData(const BlockPos& pos, BlockData state) = 0;
};