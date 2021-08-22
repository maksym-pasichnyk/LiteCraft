#pragma once

#include "ContainerBlock.hpp"

struct StructureBlock : ContainerBlock {
    struct Payload {
        uint16_t mode : 2;
        uint16_t : 14;
    };

    static constexpr auto MODE = BlockStateProperty::STRUCTURE_BLOCK_MODE;

    using ContainerBlock::ContainerBlock;
};