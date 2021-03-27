#pragma once

#include "Block.hpp"
#include "../particles/ParticleTypes.hpp"

struct CoralBlock : Block {
    CoralBlock(int id, Block* block, Properties properties) : Block(id, std::move(properties)) {}
};