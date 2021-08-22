#pragma once

#include "Block.hpp"

struct AirBlock : Block {
    using Block::Block;

    RenderType getRenderType() const override {
        return RenderType::Air;
    }
};