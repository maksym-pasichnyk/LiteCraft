#pragma once

#include "ids.hpp"

#include <cstdint>

struct BlockData {
    BlockID id = BlockID::AIR;
    uint16_t val = 0;

    bool isAir() const {
        return id == BlockID::AIR;
    }
};

static bool isOpaque(BlockData data) {
    if (data.id == BlockID::AIR ||
        data.id == BlockIDs::torch) {
        return false;
    }

    return true;
}

static int32_t getLightFor(BlockData data) {
    if (data.id == BlockIDs::torch) {
        return 14;
    }
    return 0;
}