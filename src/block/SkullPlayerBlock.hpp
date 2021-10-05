#pragma once

#include "SkullBlock.hpp"

struct SkullPlayerBlock : SkullBlock {
    SkullPlayerBlock(int id, BlockBehaviour behaviour) : SkullBlock(id, Type::PLAYER, std::move(behaviour)) {}
};