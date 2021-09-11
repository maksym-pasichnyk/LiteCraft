#pragma once

#include <util/math/BlockPos.hpp>

struct TemperatureModifiers {
    static auto none(const BlockPos& pos, float temperature) -> float;
    static auto frozen(const BlockPos& pos, float temperature) -> float;
};

