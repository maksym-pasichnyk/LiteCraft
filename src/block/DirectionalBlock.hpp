#pragma once

#include "Block.hpp"

struct DirectionalBlock : Block {
    static constexpr auto FACING = BlockStateProperty::HORIZONTAL_FACING;

    using Block::Block;
};