#pragma once

using TemperatureModifier = auto(*)(const BlockPos& pos, float temperature) -> float;
