#pragma once

#include "Block.hpp"

struct FlowerPotBlock : Block {
    FlowerPotBlock(int id, Block* block, BlockBehaviour behaviour) : Block(id, std::move(behaviour)) {}
};