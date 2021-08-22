#pragma once

#include "Block.hpp"

struct SixWayBlock : Block {
    static constexpr auto NORTH = BlockStateProperty::NORTH;
    static constexpr auto EAST = BlockStateProperty::EAST;
    static constexpr auto SOUTH = BlockStateProperty::SOUTH;
    static constexpr auto WEST = BlockStateProperty::WEST;
    static constexpr auto UP = BlockStateProperty::UP;
    static constexpr auto DOWN = BlockStateProperty::DOWN;

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