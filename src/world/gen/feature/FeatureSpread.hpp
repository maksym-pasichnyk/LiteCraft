#pragma once

#include "../../../util/Random.hpp"

struct FeatureSpread {
    int base = 0;
    int spread = 0;

    int getCount(Random& random) const {
        return spread == 0 ? base : (base + random.nextInt(spread + 1));
    }
};