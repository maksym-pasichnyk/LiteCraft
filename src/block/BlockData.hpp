#pragma once

#include "Block.hpp"

#include <cstdint>

struct BlockData {
    uint16_t id = 0;
    uint16_t val = 0;

    bool isAir() const {
        return id == 0;
    }

    bool isIn(Block* block) const {
        return id == block->id;
    }

    Block* getBlock() const {
        return Block::id_to_block[static_cast<size_t>(id)];
    }
};

static bool isOpaque(BlockData data) {
    if (data.isAir()) {
        return false;
    }

    auto block = data.getBlock();

    if (block == Block::lava) {
        return false;
    }

    if (block->renderLayer == RenderLayer::Transparent) {
        return false;
    }

    if (block->renderType != RenderType::Block) {
        return false;
    }

    return true;
}

static int32_t getLightFor(BlockData data) {
    if (data.isIn(Block::torch)) {
        return 14;
    }
    if (data.isIn(Block::lava)) {
        return 14;
    }
    if (data.isIn(Block::flowing_lava)) {
        return 14;
    }
    return 0;
}