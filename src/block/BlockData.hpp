#pragma once

#include <cstdint>
#include <compare>

struct Block;

struct BlockData {
    uint16_t id = 0;
    uint16_t val = 0;

    constexpr auto operator<=>(const BlockData&) const noexcept = default;

    bool isAir() const {
        return id == 0;
    }

    bool isIn(Block* block) const {
        return block == getBlock();
    }

    Block* getBlock() const;
    bool isOpaque() const;
    int32_t getLightLevel() const;
};