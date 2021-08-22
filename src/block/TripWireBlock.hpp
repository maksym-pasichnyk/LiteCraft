#pragma once

#include "Block.hpp"

struct TripWireHookBlock;
struct TripWireBlock : Block {
    struct Payload {
        uint16_t powered : 1;
        uint16_t attached : 1;
        uint16_t disarmed : 1;
        uint16_t north : 1;
        uint16_t south : 1;
        uint16_t east : 1;
        uint16_t west : 1;
        uint16_t : 9;
    };

    static constexpr auto POWERED = BlockStateProperty::POWERED;
    static constexpr auto ATTACHED = BlockStateProperty::ATTACHED;
    static constexpr auto DISARMED = BlockStateProperty::DISARMED;
    static constexpr auto NORTH = BlockStateProperty::NORTH;
    static constexpr auto EAST = BlockStateProperty::EAST;
    static constexpr auto SOUTH = BlockStateProperty::SOUTH;
    static constexpr auto WEST = BlockStateProperty::WEST;

    TripWireBlock(int id, TripWireHookBlock* block, Properties properties) : Block(id, std::move(properties)) {}
};