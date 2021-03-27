#pragma once

#include "Block.hpp"
#include "../potion/Effects.hpp"

struct WitherRoseBlock : Block {
    WitherRoseBlock(int id, Effects effect, Properties properties) : Block(id, std::move(properties)) {}
};