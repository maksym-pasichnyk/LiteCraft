#pragma once

#include "SkullBlock.hpp"

struct WitherSkeletonSkullBlock : SkullBlock {
    WitherSkeletonSkullBlock(int id, BlockBehaviour behaviour) : SkullBlock(id, Type::WITHER_SKELETON, std::move(behaviour)) {}
};