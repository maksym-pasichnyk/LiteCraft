#pragma once

#include <optional>

struct TwoLayerFeature {
    int limit;
    int lower_size;
    int upper_size;
    std::optional<int> min_clipped_height;

    int func_230369_a_(int min, int max) const {
        return max < limit ? lower_size : upper_size;
    }
};