#pragma once

#include "Asset/Asset.hpp"

#include "Logger/Logger.hpp"

namespace eng {

class Sound_ : public Asset {
public:
    Sound_(Mix_Chunk* sound);

    ~Sound_();

    void play(int channel = -1, int loop = 0);
    void play_fade(int time, int channel = -1, int loop = 0);
    void volume(float volume);

private:
    Mix_Chunk* m_sound;
};

typedef Sound_* Sound;

}