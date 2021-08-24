#pragma once

#include "WallSkullBlock.hpp"

struct SkullWallPlayerBlock : WallSkullBlock {
    SkullWallPlayerBlock(int id, Properties properties) : WallSkullBlock(id, SkullBlock::Type::PLAYER, std::move(properties)) {}
};