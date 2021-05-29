#pragma once

#include "ScalingSettings.hpp"
#include "SlideSettings.hpp"

struct NoiseSettings {
    ScalingSettings sampling;
    SlideSettings topSlide;
    SlideSettings bottomSlide;
    int height;
    int sizeVertical;
    int sizeHorizontal;
    double destinyFactor;
    double densityOffset;
    bool randomDensityOffset;
    bool islandNoiseOverride;
    bool amplified;
};