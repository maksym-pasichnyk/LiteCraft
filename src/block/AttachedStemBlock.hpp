#pragma once

#include "Block.hpp"

struct StemGrownBlock;

struct AttachedStemBlock : Block {
    AttachedStemBlock(int id, StemGrownBlock* block, Properties properties) : Block(id, std::move(properties)) {}
};