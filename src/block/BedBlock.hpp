#pragma once

#include "Block.hpp"

struct BedBlock : Block {
    BedBlock(int id, DyeColors color, Properties properties) : Block(id, std::move(properties)) {}
};