#pragma once

#include "Block.hpp"

struct TripWireHookBlock;
struct TripWireBlock : Block {
    TripWireBlock(int id, TripWireHookBlock* block, Properties properties) : Block(id, std::move(properties)) {}
};