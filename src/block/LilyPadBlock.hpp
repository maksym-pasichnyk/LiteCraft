#pragma once

#include "BushBlock.hpp"

struct LilyPadBlock : BushBlock {
    using BushBlock::BushBlock;

    TintType getTintType() const override {
        return TintType::Grass;
    }

    RenderType getRenderType() const override {
        return RenderType::LilyPad;
    }

    bool isValidGround(const BlockData& data, WorldReader &reader, const BlockPos &pos) override;
};