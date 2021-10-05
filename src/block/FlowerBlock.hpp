#pragma once

#include "BushBlock.hpp"
#include "../potion/Effects.hpp"

struct FlowerBlock : BushBlock {
    FlowerBlock(int id, Effects effect, int duration, BlockBehaviour behaviour) : BushBlock(id, std::move(behaviour)) {}
};