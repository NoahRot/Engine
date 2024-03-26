#pragma once

#include <iostream>
#include <string>
#include <External/SDL2/SDL_mixer.h>

#include "Logger/Logger.hpp"
#include "Core/UniqueIndex.hpp"
#include "Asset/Asset.hpp"

namespace eng {

class Music_ : public Asset {
public:
    Music_(Mix_Music* music);

    ~Music_();

    void play(int32_t loop = 0) const;

    void play_fade(int32_t time, int32_t loop = 0) const;

    static void volume(float volume);

    static void pause();

    static bool is_playing();

    static void resume();

    static void stop();
    
    static void stop_fade(int32_t time);

private:
    Mix_Music* m_music;
};

typedef Music_* Music;

}