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