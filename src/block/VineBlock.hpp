#pragma once

#include "Block.hpp"

struct WorldReader;
enum class Direction;

struct VineBlock : Block {
    using Block::Block;

    static bool canAttachTo(WorldReader& reader, const BlockPos& pos, Direction direction) {
        return false;
    }
};