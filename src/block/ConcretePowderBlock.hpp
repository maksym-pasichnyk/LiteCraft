#pragma once

#include "FallingBlock.hpp"

struct ConcretePowderBlock : FallingBlock {
    ConcretePowderBlock(int id, Block* block, Properties properties) : FallingBlock(id, std::move(properties)) {}
};