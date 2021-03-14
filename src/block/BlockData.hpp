#pragma once

#include "Block.hpp"

#include <cstdint>

struct BlockData {
    uint16_t id = 0;
    uint16_t val = 0;

    bool isAir() const {
        return id == 0;
    }
};

static bool isOpaque(BlockData data) {
    if (data.isAir()) {
        return false;
    }

    auto block = Block::id_to_block.at(data.id);

    if (block->renderLayer == RenderLayer::Transparent) {
        return false;
    }

    if (block->renderType != RenderType::Block) {
        return false;
    }

    return true;
}

static int32_t getLightFor(BlockData data) {
    if (data.id == Block::torch->id) {
        return 14;
    }
    return 0;
}