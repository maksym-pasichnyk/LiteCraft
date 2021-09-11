#pragma once

#include <sounds/SoundEvent.hpp>

struct BackgroundMusicTrack {
    SoundEvent sound;
    int minDelay;
    int maxDelay;
    bool replaceCurrentMusic;

    static auto from(SoundEvent sound) -> BackgroundMusicTrack {
        return {
            .sound = std::move(sound),
            .minDelay = 12000,
            .maxDelay = 24000,
            .replaceCurrentMusic = false
        };
    }
};