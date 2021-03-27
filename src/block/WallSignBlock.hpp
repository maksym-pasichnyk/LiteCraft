#pragma once

#include "Block.hpp"
#include "WoodType.hpp"

struct WallSignBlock : Block {
    WallSignBlock(int id, Properties properties, WoodType woodType) : Block(id, std::move(properties)) {}
};