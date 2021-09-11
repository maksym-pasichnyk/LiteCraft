#include "MoodSoundAmbiences.hpp"
#include <sounds/SoundEvents.hpp>

MoodSoundAmbience MoodSoundAmbiences::DEFAULT_CAVE = MoodSoundAmbience{
    .sound = SoundEvents::AMBIENT_CAVE,
    .delay = 6000,
    .radius = 8,
    .offset = 2.0
};