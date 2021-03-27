#pragma once

#include "Block.hpp"

struct StairsBlock : Block {
    StairsBlock(int id, BlockData data, Properties properties) : Block(id, std::move(properties)) {}
};