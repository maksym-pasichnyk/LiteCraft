#pragma once

#include "Block.hpp"

struct LeavesBlock : Block {
    using Block::Block;

    TintType getTintType() const override {
        return TintType::Foliage;
    }

    RenderType getRenderType() const override {
        return RenderType::Leaves;
    }

    RenderLayer getRenderLayer() const override {
        return RenderLayer::Cutout;
    }
};