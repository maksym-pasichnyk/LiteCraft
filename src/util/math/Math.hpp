#pragma once

struct Math {
    static constexpr int floorDiv(int x, int y) {
        int r = x / y;
        // if the signs are different and modulo not zero, round down
        if ((x ^ y) < 0 && (r * y != x)) {
            r--;
        }
        return r;
    }

    static constexpr int64_t floorMod(int64_t x, int64_t y) {
//        return x - floorDiv(x, y) * y;
        return ((x % y) + y) % y;
    }

    static constexpr int64_t lfloor(double value) {
        const int64_t i = static_cast<int64_t>(value);
        return value < static_cast<double>(i) ? i - static_cast<int64_t>(1) : i;
    }

    static constexpr float lerp(float pct, float start, float end) {
        return start + pct * (end - start);
    }

    static constexpr double lerp(double pct, double start, double end) {
        return start + pct * (end - start);
    }

    static constexpr double clamp(double num, double min, double max) {
        return num < min ? min : num > max ? max : num;
    }

    static constexpr double clampedLerp(double lowerBnd, double upperBnd, double slide) {
        return slide < 0.0 ? lowerBnd : slide > 1.0 ? upperBnd : lerp(slide, lowerBnd, upperBnd);
    }
};