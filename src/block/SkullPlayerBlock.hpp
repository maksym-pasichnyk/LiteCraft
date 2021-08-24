#pragma once

#include "SkullBlock.hpp"

struct SkullPlayerBlock : SkullBlock {
    SkullPlayerBlock(int id, Properties properties) : SkullBlock(id, Type::PLAYER, std::move(properties)) {}
};