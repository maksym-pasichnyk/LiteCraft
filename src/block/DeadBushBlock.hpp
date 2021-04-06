#pragma once

#include "BushBlock.hpp"

struct DeadBushBlock : BushBlock {
    using BushBlock::BushBlock;

    bool isValidGround(const BlockData& data, WorldReader& reader, const BlockPos& pos) override;
};