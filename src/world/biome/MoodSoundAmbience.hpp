#pragma once

#include <sounds/SoundEvent.hpp>

struct MoodSoundAmbience {
    SoundEvent sound;
    int delay;
    int radius;
    double offset;
};