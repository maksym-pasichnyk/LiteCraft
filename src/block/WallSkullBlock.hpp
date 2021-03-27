#pragma once

#include "Block.hpp"
#include "SkullBlock.hpp"

struct WallSkullBlock : Block {
    WallSkullBlock(int id, SkullBlock::Types type, Properties properties) : Block(id, std::move(properties)) {}
};