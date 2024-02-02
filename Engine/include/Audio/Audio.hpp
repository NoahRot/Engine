#pragma once

#include <iostream>
#include <map>
#include <stack>

#include "Audio/Music.hpp"
#include "Core/Type.hpp"
#include "Core/CoreFnc.hpp"

namespace eng {

struct Music {
    Index id;
};

struct Sound {
    Index id;
};

class Audio {
public:

    // === Class singleton methods and delete ===

    ~Audio();

    Audio(const Audio&) = delete;
    Audio& operator=(const Audio&) = delete;

    static Audio& Instance();

    // === Loader, Free and checker ===

    Music LoadMusic(const std::string& path);

    Sound LoadSound(const std::string& path);

    void FreeMusic(Music music);

    void FreeSound(Sound sound);

    bool MusicValidity(Music music);

    bool SoundValidity(Sound sound);

    // === Music ===

    void PlayMusic(Music music, int32_t loop = 0);

    void PlayFadeMusic(Music music, int32_t time, int32_t loop = 0);

    void VolumeMusic(float volume) const;

    void PauseMusic() const;

    bool IsMusicPlaying() const;

    void ResumeMusic() const;

    void StopFadeMusic(int time) const;

    void StopMusic() const;

    // === Sound ===

    void PlaySound(Sound sound, int channel = -1, int loop = 0);

    void PlayFadeSound(Sound sound, int time, int channel = -1, int loop = 0);

    void VolumeSound(Sound sound, float volume);

private:
    Audio();

    Index m_nextMusicID;
    std::map<Index, Mix_Music*> m_listMusic;
    std::stack<Index> m_musicAvaiableIndex;

    Index m_nextSoundID;
    std::map<Index, Mix_Chunk*> m_listSound;
    std::stack<Index> m_soundAvaiableIndex;

};

}