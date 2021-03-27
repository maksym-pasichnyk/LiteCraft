#pragma once

#include "Block.hpp"
#include "../particles/ParticleTypes.hpp"

struct WallTorchBlock : Block {
    WallTorchBlock(int id, Properties properties, ParticleTypes particleType) : Block(id, std::move(properties)) {}
};