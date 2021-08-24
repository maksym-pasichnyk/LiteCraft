#pragma once

#include "PaneBlock.hpp"
#include "material/DyeColors.hpp"

struct StainedGlassPaneBlock : PaneBlock {
    StainedGlassPaneBlock(int id, DyeColors color, Properties properties) : PaneBlock(id, std::move(properties)) {}
};