#pragma once

#include "FallingBlock.hpp"

struct SandBlock : FallingBlock {
    explicit SandBlock(int id, int color, Properties properties) : FallingBlock(id, std::move(properties)) {}
};