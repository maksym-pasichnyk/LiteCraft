#pragma once

#include "Block.hpp"

struct PistonBlock : Block {
    PistonBlock(int id, bool sticky, Properties properties) : Block(id, std::move(properties)) {}
};