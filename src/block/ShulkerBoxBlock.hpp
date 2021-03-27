#pragma once

#include "Block.hpp"
#include "material/DyeColors.hpp"

#include <optional>

struct ShulkerBoxBlock : Block {
    ShulkerBoxBlock(int id, std::optional<DyeColors> color, Properties properties) : Block(id, std::move(properties)) {}
};