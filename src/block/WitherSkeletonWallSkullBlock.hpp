#pragma once

#include "WallSkullBlock.hpp"

struct WitherSkeletonWallSkullBlock : WallSkullBlock {
    WitherSkeletonWallSkullBlock(int id, BlockBehaviour behaviour) : WallSkullBlock(id, SkullBlock::Type::WITHER_SKELETON, std::move(behaviour)) {}
};