#pragma once

#include <iostream>
#include <string>
#include <External/SDL2/SDL_mixer.h>

#include "Core/Type.hpp"

#include "Audio/Audio.hpp"

namespace eng {

class Music {
public:
    Music();
    ~Music();

    bool Load(const std::string& path);
    bool IsValid() const;
    Index GetIndex() const;

    void Play(int32_t loop = 0) const;
    void PlayFade(int32_t time, int32_t loop = 0) const;

    static void Volume(float volume);
    static void Pause();
    static bool IsPlaying();
    static void Resume();
    static void Stop();
    static void StopFade(int32_t time);

private:
    bool m_valid;
    Index m_index;
    Mix_Music* m_music;
};

}