#pragma once

#include "CoralFanBlock.hpp"

struct CoralFinBlock : CoralFanBlock {
    CoralFinBlock(int id, Block* block, BlockBehaviour behaviour) : CoralFanBlock(id, std::move(behaviour)) {}
};