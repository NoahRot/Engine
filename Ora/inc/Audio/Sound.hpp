#pragma once

#include <SDL2/SDL_mixer.h>

namespace ora {

class Sound {
public:

private:
    Mix_Chunk* m_sound;
};

}