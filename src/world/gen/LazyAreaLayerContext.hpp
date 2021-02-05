#pragma once

#include "IExtendedNoiseRandom.hpp"
#include "ImprovedNoiseGenerator.hpp"
#include "../../util/FastRandom.hpp"

#include <memory>

class LazyAreaLayerContext : public virtual IExtendedNoiseRandom {
public:
    int64_t seed;
    int64_t positionSeed;
    ImprovedNoiseGenerator noise;

public:
    LazyAreaLayerContext(int64_t _seed, int64_t seedModifier)
        : seed(hash(_seed, seedModifier))
        , noise(Random::from(_seed)) {}

    ImprovedNoiseGenerator& getNoiseGenerator() override {
        return noise;
    }

    void setPosition(int64_t x, int64_t z) override {
        int64_t i = seed;
        i = FastRandom::mix(i, x);
        i = FastRandom::mix(i, z);
        i = FastRandom::mix(i, x);
        i = FastRandom::mix(i, z);
        positionSeed = i;
    }

    static int64_t floorDiv(int64_t x, int64_t y) {
        int64_t r = x / y;
        // if the signs are different and modulo not zero, round down
        if ((x ^ y) < 0 && (r * y != x)) {
            r--;
        }
        return r;
    }

    static int64_t floorMod(int64_t x, int64_t y) {
//        return x - floorDiv(x, y) * y;
        return ((x % y) + y) % y;
    }

    int32_t random(int32_t bound) override {
        const auto i = static_cast<int32_t>(floorMod(positionSeed >> 24, bound));
        positionSeed = FastRandom::mix(positionSeed, seed);
        return i;
    }

private:
    static constexpr int64_t hash(int64_t left, int64_t right) noexcept {
        int64_t x = FastRandom::mix(right, right);
        x = FastRandom::mix(x, right);
        x = FastRandom::mix(x, right);
        int64_t y = FastRandom::mix(left, x);
        y = FastRandom::mix(y, x);
        return FastRandom::mix(y, x);
    }
};