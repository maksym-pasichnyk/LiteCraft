#pragma once

#include <optional>

struct BiomeAmbience {
    int fogColor;
    int waterColor;
    int waterFogColor;
    int skyColor;
    std::optional<int> foliageColor;
    std::optional<int> grassColor;
//    GrassColorModifier grassColorModifier;
//    std::optional<ParticleEffectAmbience> particle;
//    std::optional<SoundEvent> ambientSound;
//    std::optional<MoodSoundAmbience> moodSound;
//    std::optional<SoundAdditionsAmbience> additionsSound;
//    std::optional<BackgroundMusicSelector> music;
};