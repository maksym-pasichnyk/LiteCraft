#pragma once

#include "Block.hpp"

struct SandBlock : Block {
    explicit SandBlock(int id, int color, Properties properties) : Block(id, std::move(properties)) {

    }
};