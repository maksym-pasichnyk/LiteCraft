#pragma once

#include "Block.hpp"

struct TurtleEggBlock : Block {
    struct Payload {
        uint16_t hatch : 3;
        uint16_t eggs : 3;
        uint16_t : 10;
    };

    static constexpr auto HATCH = BlockStateProperty::HATCH_0_2;
    static constexpr auto EGGS = BlockStateProperty::EGGS_1_4;

    using Block::Block;
};