#pragma once

#include <util/math/BlockPos.hpp>

struct TemperatureModifiers {
    static float none(BlockPos pos, float temperature);
    static float frozen(BlockPos pos, float temperature);
};

