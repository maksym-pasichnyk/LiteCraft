#pragma once

#include "WallSkullBlock.hpp"

struct WitherSkeletonWallSkullBlock : WallSkullBlock {
    WitherSkeletonWallSkullBlock(int id, Properties properties) : WallSkullBlock(id, SkullBlock::Type::WITHER_SKELETON, std::move(properties)) {}
};