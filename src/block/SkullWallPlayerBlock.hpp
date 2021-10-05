#pragma once

#include "WallSkullBlock.hpp"

struct SkullWallPlayerBlock : WallSkullBlock {
    SkullWallPlayerBlock(int id, BlockBehaviour behaviour) : WallSkullBlock(id, SkullBlock::Type::PLAYER, std::move(behaviour)) {}
};