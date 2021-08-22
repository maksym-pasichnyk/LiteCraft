#pragma once

#include "ContainerBlock.hpp"
#include "WoodType.hpp"

struct AbstractSignBlock : ContainerBlock {
    AbstractSignBlock(int id, Properties properties, WoodType woodType) : ContainerBlock(id, std::move(properties)) {}
};