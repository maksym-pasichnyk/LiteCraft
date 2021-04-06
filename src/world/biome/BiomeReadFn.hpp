#pragma once

#include "../../util/math/BlockPos.hpp"

#include <functional>

struct Biome;
using BiomeReadFn = std::function<Biome*(BlockPos)>;