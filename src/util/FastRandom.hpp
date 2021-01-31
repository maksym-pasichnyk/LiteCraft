#pragma once

#include <cstdint>

class FastRandom {
public:
    static constexpr int64_t mix(int64_t left, int64_t right) noexcept {
        return left * (left * 6364136223846793005LL + 1442695040888963407LL) + right;
    }
};