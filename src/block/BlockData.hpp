#pragma once

#include "Block.hpp"
#include "Blocks.hpp"

#include <cstdint>

struct BlockData {
    uint16_t id = 0;
    uint16_t val = 0;

    constexpr auto operator<=>(const BlockData&) const noexcept = default;

    bool isAir() const {
        return id == 0;
    }

    bool isIn(Block* block) const {
        return id == block->id;
    }

    Block* getBlock() const {
        return Blocks::id_to_block[static_cast<size_t>(id)];
    }
};

static bool isOpaque(BlockData data) {
    if (data.isAir()) {
        return false;
    }

    auto block = data.getBlock();

    if (block == Blocks::lava) {
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
    if (data.isIn(Blocks::torch)) {
        return 14;
    }
    if (data.isIn(Blocks::lava)) {
        return 14;
    }
    if (data.isIn(Blocks::flowing_lava)) {
        return 14;
    }
    return 0;
}