#pragma once

#include "Block.hpp"

struct RotatedPillarBlock : Block {
    static constexpr auto AXIS = BlockStateProperty::AXIS;

    using Block::Block;
};