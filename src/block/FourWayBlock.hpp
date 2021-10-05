#pragma once

#include "Block.hpp"

struct FourWayBlock : Block {
    static constexpr auto EAST = Property::EAST;
    static constexpr auto NORTH = Property::NORTH;
    static constexpr auto SOUTH = Property::SOUTH;
    static constexpr auto WEST = Property::WEST;

    using Block::Block;
};