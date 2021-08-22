#pragma once

#include "Block.hpp"

struct TripWireHookBlock : Block {
    struct Payload {
        uint16_t facing : 3;
        uint16_t attached : 1;
        uint16_t powered : 1;
        uint16_t : 11;
    };

    static constexpr auto FACING = BlockStateProperty::HORIZONTAL_FACING;
    static constexpr auto POWERED = BlockStateProperty::POWERED;
    static constexpr auto ATTACHED = BlockStateProperty::ATTACHED;

    using Block::Block;
};