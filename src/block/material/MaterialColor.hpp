#pragma once

#include <cstdint>

struct MaterialColor {
    uint32_t colorIndex;
    uint32_t colorValue;

    constexpr uint32_t getMapColor(int index) noexcept {
        int i = 220;
        if (index == 0) {
            i = 180;
        }
        if (index == 1) {
            i = 220;
        }
        if (index == 2) {
            i = 255;
        }
        if (index == 3) {
            i = 135;
        }
        const uint32_t r = ((colorValue >> 16) & 255) * i / 255;
        const uint32_t g = ((colorValue >> 8) & 255) * i / 255;
        const uint32_t b = ((colorValue >> 0) & 255) * i / 255;
        return 0xFF000000 | (b << 16) | (g << 8) | r;
    }
};

