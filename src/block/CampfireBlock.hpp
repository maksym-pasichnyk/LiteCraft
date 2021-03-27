#pragma once

#include "Block.hpp"

struct CampfireBlock : Block {
    CampfireBlock(int id, bool smokey, int fireDamage, Properties properties) : Block(id, std::move(properties)) {}
};