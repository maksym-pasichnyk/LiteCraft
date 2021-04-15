#pragma once

enum class MineshaftType {
    NORMAL,
    MESA
};

struct MineshaftConfig {
    float probability;
    MineshaftType type;
};