#pragma once

#include "Block.hpp"

struct ConcretePowderBlock : Block {
    ConcretePowderBlock(int id, Block* block, Properties properties) : Block(id, std::move(properties)) {}
};