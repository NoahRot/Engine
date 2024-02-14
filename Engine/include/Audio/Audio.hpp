#pragma once

#include <iostream>
#include <map>
#include <stack>

#include "Audio/Music.hpp"
#include "Audio/Sound.hpp"

#include "Core/Type.hpp"
#include "Core/CoreFnc.hpp"

namespace eng {

class Sound;
class Music;

Music* CreateMusic(const std::string& path);

Sound* CreateSound(const std::string& path);

namespace _intern_ {
class Audio {
public:

    // === Class singleton methods and delete ===

    ~Audio();

    Audio(const Audio&) = delete;
    Audio& operator=(const Audio&) = delete;

    static Audio& Instance();



    void AddMusic(Music* music);

    void RemoveMusic(Music* music);

    Index GetMusicIndex();



    void AddSound(Sound* sound);

    void RemoveSound(Sound* sound);

    Index GetSoundIndex();

private:
    Audio();

    Index m_nextMusicID;
    std::map<Index, Music*> m_listMusic;
    std::stack<Index> m_musicAvaiableIndex;

    Index m_nextSoundID;
    std::map<Index, Sound*> m_listSound;
    std::stack<Index> m_soundAvaiableIndex;

};
}

}