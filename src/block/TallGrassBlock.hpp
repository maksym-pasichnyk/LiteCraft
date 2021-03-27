#pragma once

#include "BushBlock.hpp"

struct TallGrassBlock : BushBlock {
    using BushBlock::BushBlock;

    TintType getTintType() const override {
        return TintType::Grass;
    }
};