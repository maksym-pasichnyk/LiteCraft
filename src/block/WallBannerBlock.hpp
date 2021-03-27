#pragma once

#include "Block.hpp"
#include "material/DyeColors.hpp"

struct WallBannerBlock : Block {
    WallBannerBlock(int id, DyeColors color, Properties properties) : Block(id, std::move(properties)) {}
};