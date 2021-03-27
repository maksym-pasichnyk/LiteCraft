#pragma once

#include "Block.hpp"

struct GrassBlock : Block {
    using Block::Block;

    TintType getTintType() const override {
        return TintType::Grass;
    }
};