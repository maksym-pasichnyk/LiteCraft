#pragma once

#include <tl/optional.hpp>
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
    tl::optional<int> foliageColor;
    tl::optional<int> grassColor;
    GrassColorModifier grassColorModifier;
    tl::optional<ParticleEffectAmbience> particle;
    tl::optional<SoundEvent> ambientSound;
    tl::optional<MoodSoundAmbience> moodSound;
    tl::optional<SoundAdditionsAmbience> additionsSound;
    tl::optional<BackgroundMusicTrack> music;
};