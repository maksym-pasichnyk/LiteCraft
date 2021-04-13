#pragma once

#include "Block.hpp"
#include "../state/BlockStateProperties.hpp"

struct SnowyDirtBlock : Block {
    static constexpr auto SNOWY = BlockStateProperty::SNOWY;

    using Block::Block;
};