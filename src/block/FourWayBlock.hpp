#pragma once

#include "Block.hpp"

struct FourWayBlock : Block {
    static constexpr auto EAST = BlockStateProperty::EAST;
    static constexpr auto NORTH = BlockStateProperty::NORTH;
    static constexpr auto SOUTH = BlockStateProperty::SOUTH;
    static constexpr auto WEST = BlockStateProperty::WEST;

    using Block::Block;
};