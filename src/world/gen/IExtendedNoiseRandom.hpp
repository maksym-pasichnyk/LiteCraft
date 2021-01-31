#pragma once

#include "INoiseRandom.hpp"
#include "src/world/gen/layer/area/IArea.hpp"

#include <cstdint>
#include <memory>

class IExtendedNoiseRandom : public virtual INoiseRandom {
public:
    virtual void setPosition(int64_t x, int64_t z) = 0;

//    int random(int bound) override {
//        return 0;
//    }

public:
    int pickRandom(int first, int second) {
        return random(2) == 0 ? first : second;
    }

    int pickRandom(int first, int second, int third, int fourth) {
        switch (random(4)) {
            case 0: return first;
            case 1: return second;
            case 2: return third;
            default: return fourth;
        }
    }
};