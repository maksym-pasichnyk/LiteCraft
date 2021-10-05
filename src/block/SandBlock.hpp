#pragma once

#include "FallingBlock.hpp"

struct SandBlock : FallingBlock {
    explicit SandBlock(int id, int color, BlockBehaviour behaviour) : FallingBlock(id, std::move(behaviour)) {}
};