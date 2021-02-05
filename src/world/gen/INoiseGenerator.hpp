#pragma once

struct INoiseGenerator {
    virtual ~INoiseGenerator() = default;
    virtual auto noiseAt(double x, double y, double z, double w) const -> double = 0;
};