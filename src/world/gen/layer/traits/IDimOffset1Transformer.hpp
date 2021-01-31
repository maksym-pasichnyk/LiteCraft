#pragma once

#include "IDimTransformer.hpp"

struct IDimOffset1Transformer {
    int getOffsetX(int x) {
        return x - 1;
    }

    int getOffsetZ(int z) {
        return z - 1;
    }
};