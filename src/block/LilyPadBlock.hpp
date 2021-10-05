#pragma once

#include "BushBlock.hpp"

struct LilyPadBlock : BushBlock {
    using BushBlock::BushBlock;

    bool isValidGround(const BlockData& data, WorldReader &reader, const BlockPos &pos) override;
};