#pragma once

#include "Block.hpp"

struct RepeaterBlock : Block {
    static constexpr auto FACING = BlockStateProperty::HORIZONTAL_FACING;

    using Block::Block;
};