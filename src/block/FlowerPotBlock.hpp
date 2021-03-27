#pragma once

#include "Block.hpp"

struct FlowerPotBlock : Block {
    FlowerPotBlock(int id, Block* block, Properties properties) : Block(id, std::move(properties)) {

    }
};