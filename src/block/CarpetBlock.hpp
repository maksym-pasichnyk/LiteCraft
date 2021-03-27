#pragma once

#include "Block.hpp"
#include "material/DyeColors.hpp"

struct CarpetBlock : Block {
    CarpetBlock(int id, DyeColors color, Properties properties) : Block(id, std::move(properties)) {}
};