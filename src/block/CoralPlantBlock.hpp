#pragma once

#include "Block.hpp"

struct CoralPlantBlock : Block {
    CoralPlantBlock(int id, Block* block, Properties properties) : Block(id, std::move(properties)) {}
};