#pragma once

#include "Block.hpp"
#include "material/DyeColors.hpp"

struct CarpetBlock : Block {
    CarpetBlock(int id, DyeColors color, BlockBehaviour behaviour) : Block(id, std::move(behaviour)) {}
};