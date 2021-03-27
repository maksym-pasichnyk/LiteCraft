#pragma once

#include "Block.hpp"

struct StemGrownBlock;
struct StemBlock : Block {
    StemBlock(int id, StemGrownBlock* block, Properties properties) : Block(id, std::move(properties)) {}
};