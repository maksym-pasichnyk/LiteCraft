#pragma once

#include "Block.hpp"

struct SkullBlock : Block {
    enum class Types {
        SKELETON,
        WITHER_SKELETON,
        PLAYER,
        ZOMBIE,
        CREEPER,
        DRAGON
    };

    SkullBlock(int id, Types type, Properties properties) : Block(id, std::move(properties)) {}
};