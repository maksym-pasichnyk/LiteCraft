#pragma once

#include "Block.hpp"

struct CoralFinBlock : Block {
    CoralFinBlock(int id, Block* block, Properties properties) : Block(id, std::move(properties)) {}
};