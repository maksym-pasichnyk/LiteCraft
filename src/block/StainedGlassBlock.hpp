#pragma once

#include "AbstractGlassBlock.hpp"
#include "material/DyeColors.hpp"

struct StainedGlassBlock : AbstractGlassBlock {
    StainedGlassBlock(int id, DyeColors color, BlockBehaviour behaviour) : AbstractGlassBlock(id, std::move(behaviour)) {}
};