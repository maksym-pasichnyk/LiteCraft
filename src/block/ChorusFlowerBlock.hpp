#pragma once

#include "Block.hpp"

struct ChorusPlantBlock;
struct ChorusFlowerBlock : Block {
    ChorusFlowerBlock(int id, ChorusPlantBlock* block, Properties properties) : Block(id, std::move(properties)) {}
};