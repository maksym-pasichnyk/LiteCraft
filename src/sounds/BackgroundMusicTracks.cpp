#include "BackgroundMusicTracks.hpp"
#include <sounds/SoundEvents.hpp>

BackgroundMusicTrack BackgroundMusicTracks::MAIN_MENU_MUSIC = BackgroundMusicTrack{
    .sound = SoundEvents::MUSIC_MENU,
    .minDelay = 20,
    .maxDelay = 600,
    .replaceCurrentMusic = true
};
BackgroundMusicTrack BackgroundMusicTracks::CREATIVE_MODE_MUSIC = BackgroundMusicTrack{
    .sound = SoundEvents::MUSIC_CREATIVE,
    .minDelay = 12000,
    .maxDelay = 24000,
    .replaceCurrentMusic = false
};
BackgroundMusicTrack BackgroundMusicTracks::CREDITS_MUSIC = BackgroundMusicTrack{
    .sound = SoundEvents::MUSIC_CREDITS,
    .minDelay = 0,
    .maxDelay = 0,
    .replaceCurrentMusic = true
};
BackgroundMusicTrack BackgroundMusicTracks::DRAGON_FIGHT_MUSIC = BackgroundMusicTrack{
    .sound = SoundEvents::MUSIC_DRAGON,
    .minDelay = 0,
    .maxDelay = 0,
    .replaceCurrentMusic = true
};
BackgroundMusicTrack BackgroundMusicTracks::END_MUSIC = BackgroundMusicTrack{
    .sound = SoundEvents::MUSIC_END,
    .minDelay = 6000,
    .maxDelay = 24000,
    .replaceCurrentMusic = true
};

BackgroundMusicTrack BackgroundMusicTracks::UNDER_WATER_MUSIC = BackgroundMusicTrack::from(SoundEvents::MUSIC_UNDER_WATER);
BackgroundMusicTrack BackgroundMusicTracks::WORLD_MUSIC = BackgroundMusicTrack::from(SoundEvents::MUSIC_GAME);