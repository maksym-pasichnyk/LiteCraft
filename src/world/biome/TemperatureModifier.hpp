#pragma once

struct BlockPos;

using TemperatureModifier = auto(*)(const BlockPos& pos, float temperature) -> float;
