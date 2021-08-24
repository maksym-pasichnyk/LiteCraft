#pragma once

#include "AbstractCoralPlantBlock.hpp"

struct CoralPlantBlock : AbstractCoralPlantBlock {
    CoralPlantBlock(int id, Block* block, Properties properties) : AbstractCoralPlantBlock(id, std::move(properties)) {}
};