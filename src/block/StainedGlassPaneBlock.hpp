#pragma once

#include "PaneBlock.hpp"
#include "material/DyeColors.hpp"

struct StainedGlassPaneBlock : PaneBlock {
    StainedGlassPaneBlock(int id, DyeColors color, BlockBehaviour behaviour) : PaneBlock(id, std::move(behaviour)) {}
};