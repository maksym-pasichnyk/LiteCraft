#pragma once

#include <cstdint>
#include <array>

struct Heightmap {
//    bool(*heightLimitPredicate)(BlockData);

    std::array<int32_t, 16 * 16> data{};

    Heightmap() {
        data.fill(-1);
    }

    int32_t& operator[](size_t i) {
        return data[i];
    }

    const int32_t& operator[](size_t i) const {
        return data[i];
    }
};