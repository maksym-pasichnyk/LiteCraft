#pragma once

#include "Block.hpp"
#include "WoodType.hpp"

struct StandingSignBlock : Block {
    StandingSignBlock(int id, Properties properties, WoodType woodType) : Block(id, std::move(properties)) {}
};