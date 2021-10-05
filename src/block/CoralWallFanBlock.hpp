#pragma once

#include "DeadCoralWallFanBlock.hpp"

struct CoralWallFanBlock : DeadCoralWallFanBlock {
    CoralWallFanBlock(int id, Block* block, BlockBehaviour behaviour) : DeadCoralWallFanBlock(id, std::move(behaviour)) {}
};