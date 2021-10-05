#pragma once

#include "Block.hpp"

struct SilverfishBlock : Block {
    SilverfishBlock(int id, Block* block, BlockBehaviour behaviour) : Block(id, std::move(behaviour)) {}
};