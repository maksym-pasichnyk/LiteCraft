#pragma once

#include "Block.hpp"

struct LeverBlock : Block {
    static constexpr auto FACE = BlockStateProperty::FACE;
    static constexpr auto FACING = BlockStateProperty::HORIZONTAL_FACING;

    using Block::Block;
};