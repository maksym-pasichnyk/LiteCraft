#pragma once

#include "Block.hpp"

struct SugarCaneBlock : Block {
    using Block::Block;

    bool isValidPosition(const BlockData& data, WorldReader &reader, const BlockPos &pos) override;

    RenderType getRenderType() const override {
        return RenderType::Cross;
    }
    RenderLayer getRenderLayer() const override {
        return RenderLayer::Cutout;
    }
};