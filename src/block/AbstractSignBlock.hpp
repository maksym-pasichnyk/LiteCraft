#pragma once

#include "ContainerBlock.hpp"
#include "WoodType.hpp"

struct AbstractSignBlock : ContainerBlock {
    AbstractSignBlock(int id, BlockBehaviour behaviour, WoodType woodType) : ContainerBlock(id, std::move(behaviour)) {}
};