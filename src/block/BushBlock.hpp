#pragma once

#include "Block.hpp"

struct BushBlock : Block {
    using Block::Block;

    virtual bool isValidGround(const BlockData& data, WorldReader &reader, const BlockPos &pos);
    bool isValidPosition(const BlockData& data, WorldReader &reader, const BlockPos &pos) override;

//    RenderType getRenderType() const override {
//        return RenderType::Cross;
//    }
//
//    RenderLayer getRenderLayer() const override {
//        return RenderLayer::Cutout;
//    }
};