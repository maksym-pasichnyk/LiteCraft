#pragma once

#include "Block.hpp"

struct PistonBlock : Block {
    static constexpr auto FACING = BlockStateProperty::FACING;

    PistonBlock(int id, bool sticky, Properties properties) : Block(id, std::move(properties)) {}
};