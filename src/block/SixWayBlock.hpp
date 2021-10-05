#pragma once

#include "Block.hpp"

struct SixWayBlock : Block {
    static constexpr auto NORTH = Property::NORTH;
    static constexpr auto EAST = Property::EAST;
    static constexpr auto SOUTH = Property::SOUTH;
    static constexpr auto WEST = Property::WEST;
    static constexpr auto UP = Property::UP;
    static constexpr auto DOWN = Property::DOWN;

    static constexpr auto FACING_TO_PROPERTY = std::array {
        DOWN,
        UP,
        NORTH,
        SOUTH,
        WEST,
        EAST
    };

    using Block::Block;


};