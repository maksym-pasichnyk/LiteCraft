#pragma once

#include "DeadCoralWallFanBlock.hpp"

struct CoralWallFanBlock : DeadCoralWallFanBlock {
    CoralWallFanBlock(int id, Block* block, Properties properties) : DeadCoralWallFanBlock(id, std::move(properties)) {}
};