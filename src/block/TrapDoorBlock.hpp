#pragma once

#include "HorizontalBlock.hpp"

struct TrapDoorBlock : HorizontalBlock {
    struct Payload {
        uint16_t facing : 3;
        uint16_t powered : 1;
        uint16_t open : 1;
        uint16_t half : 1;
        uint16_t : 10;
    };

    static constexpr auto OPEN = BlockStateProperty::OPEN;
    static constexpr auto HALF = BlockStateProperty::HALF;
    static constexpr auto POWERED = BlockStateProperty::POWERED;

    using HorizontalBlock::HorizontalBlock;
};