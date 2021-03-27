#pragma once

#include "Block.hpp"
#include "material/DyeColors.hpp"

struct StainedGlassPaneBlock : Block {
    StainedGlassPaneBlock(int id, DyeColors color, Properties properties) : Block(id, std::move(properties)) {}
};