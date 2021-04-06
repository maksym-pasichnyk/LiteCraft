#pragma once

#include "Block.hpp"

struct CactusBlock : Block {
    using Block::Block;

    bool isValidPosition(const BlockData& data, WorldReader &reader, const BlockPos &pos) override;

    RenderType getRenderType() const override {
        return RenderType::Cactus;
    }

    RenderLayer getRenderLayer() const override {
        return RenderLayer::Cutout;
    }
};