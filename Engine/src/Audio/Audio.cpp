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

Sound* CreateSound(const std::string& path) {
    Sound* sound = new Sound;
    sound->Load(path);
    if (!sound->IsValid()) {
        delete sound;
        sound = nullptr;
    }
    return sound;
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
        if (music.second) {
            delete music.second;
        }
    }

    // Free sound
    for(auto& sound : m_listSound) {
        if (sound.second) {
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
    m_listMusic.erase(music->GetIndex());
    m_musicAvaiableIndex.push(music->GetIndex());
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
    m_listSound.erase(sound->GetIndex());
    m_soundAvaiableIndex.push(sound->GetIndex());
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