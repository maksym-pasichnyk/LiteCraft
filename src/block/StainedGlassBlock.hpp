#pragma once

#include "AbstractGlassBlock.hpp"
#include "material/DyeColors.hpp"

struct StainedGlassBlock : AbstractGlassBlock {
    StainedGlassBlock(int id, DyeColors color, Properties properties) : AbstractGlassBlock(id, std::move(properties)) {}
};