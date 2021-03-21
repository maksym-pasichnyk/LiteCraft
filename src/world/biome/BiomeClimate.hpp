#pragma once

#include "RainType.hpp"
#include "TemperatureModifier.hpp"

struct BiomeClimate {
    RainType precipitation;
    float temperature;
    TemperatureModifier temperatureModifier;
    float downfall;
};