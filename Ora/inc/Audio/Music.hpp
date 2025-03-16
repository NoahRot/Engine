#pragma once

#include <SDL2/SDL_mixer.h>

namespace ora {

class Music {
public:
    Music(Mix_Music* music) 
    : m_music(music)
    {}

    ~Music() {
        Mix_FreeMusic(m_music);
    }

    void play(int32_t loop = 0) const {
        Mix_PlayMusic(m_music, loop);
    }

    void play_fade(int32_t time_fade, int32_t loop = 0) const {
        Mix_FadeInMusic(m_music, loop, time_fade);
    }

    static void volume(float vol) {
        vol *= MIX_MAX_VOLUME;
        Mix_VolumeMusic(vol);
    }

    static void pause() {
        Mix_PauseMusic();
    }

    static void resume() {
        Mix_ResumeMusic();
    }

    static void stop() {
        Mix_HaltMusic();
    }

    static bool is_playing() {
        return Mix_PlayingMusic();
    }

    static bool is_paused() {
        return Mix_PausedMusic();
    }

private:
    Mix_Music* m_music;
};

}