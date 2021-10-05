#pragma once

#include "HorizontalBlock.hpp"

struct HorizontalFaceBlock : HorizontalBlock {
    static constexpr auto FACE = Property::FACE;

    using HorizontalBlock::HorizontalBlock;
};