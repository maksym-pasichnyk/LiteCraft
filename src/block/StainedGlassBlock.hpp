#pragma once

#include "Block.hpp"
#include "material/DyeColors.hpp"

struct StainedGlassBlock : Block {
    StainedGlassBlock(int id, DyeColors color, Properties properties) : Block(id, std::move(properties)) {}
};