#pragma once

#include "FlowerBlock.hpp"
#include "../potion/Effects.hpp"

struct WitherRoseBlock : FlowerBlock {
    WitherRoseBlock(int id, Effects effect, BlockBehaviour behaviour) : FlowerBlock(id, effect, 8, std::move(behaviour)) {}
};