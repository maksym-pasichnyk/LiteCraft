#pragma once

#include "BushBlock.hpp"

struct SweetBerryBushBlock : BushBlock {
    struct Payload {
        uint16_t age : 2;
        uint16_t : 14;
    };

    static constexpr auto AGE = BlockStateProperty::AGE_0_3;

    using BushBlock::BushBlock;
};