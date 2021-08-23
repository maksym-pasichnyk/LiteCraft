#pragma once

#include "Block.hpp"

struct RedstoneWireBlock : Block {
//    static constexpr auto POWERED = BlockStateProperty::POWERED;
//    static constexpr auto ATTACHED = BlockStateProperty::ATTACHED;
//    static constexpr auto DISARMED = BlockStateProperty::DISARMED;
    static constexpr auto NORTH = BlockStateProperty::REDSTONE_NORTH;
    static constexpr auto EAST = BlockStateProperty::REDSTONE_EAST;
    static constexpr auto SOUTH = BlockStateProperty::REDSTONE_SOUTH;
    static constexpr auto WEST = BlockStateProperty::REDSTONE_WEST;

    using Block::Block;
};