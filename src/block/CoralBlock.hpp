#pragma once

#include "../particles/ParticleType.hpp"
#include "Block.hpp"

struct CoralBlock : Block {
    CoralBlock(int id, Block* block, BlockBehaviour behaviour) : Block(id, std::move(behaviour)) {}
};