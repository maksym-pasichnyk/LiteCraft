#pragma once

#include "../particles/ParticleType.hpp"
#include "Block.hpp"

struct CoralBlock : Block {
    CoralBlock(int id, Block* block, Properties properties) : Block(id, std::move(properties)) {}
};