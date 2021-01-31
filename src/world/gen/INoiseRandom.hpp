#pragma once

class ImprovedNoiseGenerator;

class INoiseRandom {
public:
//    INoiseRandom() = default;
//    INoiseRandom(const INoiseRandom&) = delete;
//    INoiseRandom& operator=(const INoiseRandom&) = delete;

public:
    virtual int random(int bound) = 0;
    virtual ImprovedNoiseGenerator& getNoiseGenerator() = 0;
};