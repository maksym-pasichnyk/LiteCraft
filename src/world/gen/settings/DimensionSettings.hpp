#pragma once

#include "NoiseSettings.hpp"
#include "../../../block/BlockData.hpp"

struct DimensionSettings {
    NoiseSettings noise;
    BlockData layer;
    BlockData fluid;
    int bedrockRoofPosition;
    int bedrockFloorPosition;
    int seaLevel;
    bool disableMobGeneration;
};