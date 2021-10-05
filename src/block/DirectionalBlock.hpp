#pragma once

#include "Block.hpp"

struct DirectionalBlock : Block {
    static constexpr auto FACING = Property::HORIZONTAL_FACING;

    using Block::Block;
};