#pragma once

#include "Audio/Audio.hpp"

namespace eng {

class Sound {
public:
    Sound();
    ~Sound();

    bool Load(const std::string& path);
    bool IsValid() const;
    Index GetIndex() const;

    void Play(int channel = -1, int loop = 0);
    void PlayFade(int time, int channel = -1, int loop = 0);
    void Volume(float volume);

private:
    bool m_valid;
    Index m_index;
    Mix_Chunk* m_sound;
};

}