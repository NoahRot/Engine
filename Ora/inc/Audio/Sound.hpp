#pragma once

#include <SDL2/SDL_mixer.h>

namespace ora {

class Sound {
public:
    Sound(Mix_Chunk* sound);

    ~Sound();

    void volume(float vol);

    void play(int channel = -1, int loop = 0);

    void play_fade(int time, int channel = -1, int loop = 0);

private:
    Mix_Chunk* m_sound;

    float m_volume;
};

}