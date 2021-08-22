#pragma once

#include "Block.hpp"

struct SugarCaneBlock : Block {
    struct Payload {
        uint16_t age : 8;
        uint16_t : 8;
    };

    static constexpr auto AGE = BlockStateProperty::AGE_0_15;

    using Block::Block;

    bool isValidPosition(const BlockData& data, WorldReader &reader, const BlockPos &pos) override;

    RenderType getRenderType() const override {
        return RenderType::Cross;
    }
    RenderLayer getRenderLayer() const override {
        return RenderLayer::Cutout;
    }
};