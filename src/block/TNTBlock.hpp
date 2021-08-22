#pragma once

#include "Block.hpp"

struct TNTBlock : Block {
    struct Payload {
        uint16_t unstable : 1;
        uint16_t : 15;
    };

    static constexpr auto UNSTABLE = BlockStateProperty::UNSTABLE;

    using Block::Block;
};