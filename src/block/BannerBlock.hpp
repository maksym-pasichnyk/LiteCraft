#pragma once

#include "Block.hpp"
#include "material/DyeColors.hpp"

struct BannerBlock : Block {
    BannerBlock(int id, DyeColors color, Properties properties) : Block(id, std::move(properties)) {}
};