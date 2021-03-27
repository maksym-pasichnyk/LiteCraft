#pragma once

#include "Block.hpp"

struct WeightedPressurePlateBlock : Block {
    WeightedPressurePlateBlock(int id, int preassure, Properties properties) : Block(id, std::move(properties)) {}
};