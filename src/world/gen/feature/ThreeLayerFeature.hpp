#pragma once

#include <optional>

struct ThreeLayerFeature {
    int limit;
    int upper_limit;
    int lower_size;
    int middle_size;
    int upper_size;
    std::optional<int> min_clipped_height;

    int func_230369_a_(int min, int max) const {
        return max < limit ? lower_size : (max >= min - upper_limit) ? upper_size : middle_size;
    }
};