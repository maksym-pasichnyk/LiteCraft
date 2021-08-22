#pragma once

#include "Block.hpp"

struct TargetBlock : Block {
    struct Payload {
        uint16_t power : 8;
        uint16_t : 8;
    };

    static constexpr auto POWER = BlockStateProperty::POWER_0_15;

    using Block::Block;
};