#pragma once

#include "FallingBlock.hpp"

struct ConcretePowderBlock : FallingBlock {
    ConcretePowderBlock(int id, Block* block, BlockBehaviour behaviour) : FallingBlock(id, std::move(behaviour)) {}
};