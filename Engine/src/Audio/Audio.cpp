#include "Audio/Audio.hpp"

namespace eng {

Music* CreateMusic(const std::string& path) {
    Music* music = new Music;
    music->Load(path);
    if (!music->IsValid()) {
        delete music;
        music = nullptr;
    }
    return music;
}

void DestroyMusic(Music* music) {
    eng::_intern_::Audio::Instance().RemoveMusic(music);
}

Sound* CreateSound(const std::string& path) {
    Sound* sound = new Sound;
    sound->Load(path);
    if (!sound->IsValid()) {
        delete sound;
        sound = nullptr;
    }
    return sound;
}

void DestroySound(Sound* sound) {
    eng::_intern_::Audio::Instance().RemoveSound(sound);
}





namespace _intern_{
Audio::Audio()
: m_nextMusicID(0), m_nextSoundID(0)
{
    // Check if the core is configure
    if (!IsConfigure()) {
        GetLogger().Fatal("Audio", "Engine is not configure");
        exit(EXIT_FAILURE);
    }

    std::cout << "DEBUG : Audio created" << std::endl;
}

Audio::~Audio() {
    // Free music
    for(auto& music : m_listMusic) {
        if (music.second != nullptr) {
            delete music.second;
        }
    }

    // Free sound
    for(auto& sound : m_listSound) {
        if (sound.second != nullptr) {
            delete sound.second;
        }
    }

    std::cout << "DEBUG : Audio destroyed" << std::endl;
}

Audio& Audio::Instance() {
    static Audio s_instance;
    return s_instance;
}

void Audio::AddMusic(Music* music) {
    m_listMusic[music->GetIndex()] = music;
}

void Audio::RemoveMusic(Music* music) {
    if (music) {
        Index index = music->GetIndex();
        delete m_listMusic[index];
        m_listMusic[index] = nullptr;
        m_soundAvaiableIndex.push(index);
    }
}

Index Audio::GetMusicIndex() {
    Index id;
    if (m_musicAvaiableIndex.empty()) {
        id = m_nextMusicID;
        m_nextMusicID++;
    }else{
        id = m_musicAvaiableIndex.top();
        m_musicAvaiableIndex.pop();
    }
    return id;
}

void Audio::AddSound(Sound* sound) {
    m_listSound[sound->GetIndex()] = sound;
}

void Audio::RemoveSound(Sound* sound) {
    if (sound) {
        Index index = sound->GetIndex();
        delete m_listMusic[index];
        m_listMusic[index] = nullptr;
        m_soundAvaiableIndex.push(index);
    }
}

Index Audio::GetSoundIndex() {
    Index id;
    if (m_soundAvaiableIndex.empty()) {
        id = m_nextSoundID;
        m_nextSoundID++;
    }else{
        id = m_soundAvaiableIndex.top();
        m_soundAvaiableIndex.pop();
    }
    return id;
}
}


}