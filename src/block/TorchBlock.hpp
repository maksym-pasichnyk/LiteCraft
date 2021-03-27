#pragma once

#include "Block.hpp"
#include "../particles/ParticleTypes.hpp"

struct TorchBlock : Block {
    TorchBlock(int id, Properties properties, ParticleTypes particleType) : Block(id, std::move(properties)) {}
};