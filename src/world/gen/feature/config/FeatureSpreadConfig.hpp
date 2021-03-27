#pragma once

#include "../FeatureSpread.hpp"

struct FeatureSpreadConfig {
    FeatureSpread spread;

    static auto create(int base) -> FeatureSpreadConfig {
        return {
            .spread{
                .base = base,
                .spread = 0
            }
        };
    }
};