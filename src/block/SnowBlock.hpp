#pragma once

#include "Block.hpp"

struct SnowBlock : Block {
    using Block::Block;

    bool isValidPosition(const BlockData& data, WorldReader &reader, const glm::ivec3 &pos) override;

    RenderType getRenderType() const override {
        return RenderType::SnowLayer;
    }
};