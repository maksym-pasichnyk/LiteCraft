#pragma once

#include "Block.hpp"
#include "../potion/Effects.hpp"

struct FlowerBlock : Block {
    FlowerBlock(int id, Effects effect, int duration, Properties properties) : Block(id, std::move(properties)) {}
};