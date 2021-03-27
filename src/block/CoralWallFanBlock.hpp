#pragma once

#include "Block.hpp"

struct CoralWallFanBlock : Block {
    CoralWallFanBlock(int id, Block* block, Properties properties) : Block(id, std::move(properties)) {}
};