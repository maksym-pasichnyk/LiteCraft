#pragma once

#include "AbstractSkullBlock.hpp"

struct SkullBlock : AbstractSkullBlock {
    enum class Type {
        SKELETON,
        WITHER_SKELETON,
        PLAYER,
        ZOMBIE,
        CREEPER,
        DRAGON
    };

    SkullBlock(int id, Type type, Properties properties) : AbstractSkullBlock(id, std::move(properties)) {}
};