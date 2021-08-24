#pragma once

#include "CoralFanBlock.hpp"

struct CoralFinBlock : CoralFanBlock {
    CoralFinBlock(int id, Block* block, Properties properties) : CoralFanBlock(id, std::move(properties)) {}
};