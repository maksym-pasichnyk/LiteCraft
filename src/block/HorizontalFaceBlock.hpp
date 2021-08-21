#pragma once

#include "HorizontalBlock.hpp"

struct HorizontalFaceBlock : HorizontalBlock {
    static constexpr auto FACE = BlockStateProperty::FACE;

    using HorizontalBlock::HorizontalBlock;
};