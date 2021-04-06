#pragma once

#include "../block/BlockData.hpp"

struct WorldWriter {
    virtual void setData(const BlockPos& pos, BlockData state) = 0;
};