#pragma once

#include "Block.hpp"

struct SilverfishBlock : Block {
    SilverfishBlock(int id, Block* block, Properties properties) : Block(id, std::move(properties)) {}
};