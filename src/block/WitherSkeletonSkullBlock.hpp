#pragma once

#include "SkullBlock.hpp"

struct WitherSkeletonSkullBlock : SkullBlock {
    WitherSkeletonSkullBlock(int id, Properties properties) : SkullBlock(id, Type::WITHER_SKELETON, std::move(properties)) {}
};