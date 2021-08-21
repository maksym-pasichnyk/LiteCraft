#pragma once

#include <block/BlockData.hpp>

struct HugeFungusConfig {
    BlockData valid_base_block;
    BlockData stem_state;
    BlockData hat_state;
    BlockData decor_state;
    bool planted;
};