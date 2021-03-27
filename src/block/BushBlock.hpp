#pragma once

#include "Block.hpp"

struct BushBlock : Block {
    using Block::Block;

    bool isValidGround(const BlockData& data, WorldReader &reader, const glm::ivec3 &pos);
    bool isValidPosition(const BlockData& data, WorldReader &reader, const glm::ivec3 &pos) override;

    RenderType getRenderType() const override {
        return RenderType::Cross;
    }

    RenderLayer getRenderLayer() const override {
        return RenderLayer::Cutout;
    }
};