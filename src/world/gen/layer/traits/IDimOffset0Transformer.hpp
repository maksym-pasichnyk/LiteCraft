#pragma once

#include "IDimTransformer.hpp"

struct IDimOffset0Transformer {
    int getOffsetX(int x) {
        return x;
    }

    int getOffsetZ(int z) {
        return z;
    }
};