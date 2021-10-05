#pragma once

#include "AbstractCoralPlantBlock.hpp"

struct CoralPlantBlock : AbstractCoralPlantBlock {
    CoralPlantBlock(int id, Block* block, BlockBehaviour behaviour) : AbstractCoralPlantBlock(id, std::move(behaviour)) {}
};