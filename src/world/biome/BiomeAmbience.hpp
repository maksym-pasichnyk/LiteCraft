#pragma once

#include <optional>
#include <sounds/BackgroundMusicTracks.hpp>
#include <world/biome/GrassColorModifier.hpp>
#include <world/biome/MoodSoundAmbiences.hpp>
#include <world/biome/SoundAdditionsAmbience.hpp>
#include <world/biome/ParticleEffectAmbience.hpp>

struct BiomeAmbience {
    int fogColor;
    int waterColor;
    int waterFogColor;
    int skyColor;
    std::optional<int> foliageColor;
    std::optional<int> grassColor;
    GrassColorModifier grassColorModifier;
    std::optional<ParticleEffectAmbience> particle;
    std::optional<SoundEvent> ambientSound;
    std::optional<MoodSoundAmbience> moodSound;
    std::optional<SoundAdditionsAmbience> additionsSound;
    std::optional<BackgroundMusicTrack> music;
};