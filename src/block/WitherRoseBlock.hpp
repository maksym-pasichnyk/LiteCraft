#pragma once

#include "FlowerBlock.hpp"
#include "../potion/Effects.hpp"

struct WitherRoseBlock : FlowerBlock {
    WitherRoseBlock(int id, Effects effect, Properties properties) : FlowerBlock(id, effect, 8, std::move(properties)) {}
};