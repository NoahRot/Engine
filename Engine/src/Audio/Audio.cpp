#include "Audio/Audio.hpp"

namespace eng {

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
            Mix_FreeMusic(music.second);
        }
    }

    // Free sound
    for(auto& sound : m_listSound) {
        if (sound.second) {
            Mix_FreeChunk(sound.second);
        }
    }

    std::cout << "DEBUG : Audio destroyed" << std::endl;
}

Audio& Audio::Instance() {
    static Audio s_instance;
    return s_instance;
}

Music Audio::LoadMusic(const std::string& path) {
    // Load the music
    Mix_Music* mixMusic = Mix_LoadMUS(path.c_str());

    // Check if the music has been loaded successfully
    if (!mixMusic) {
        GetLogger().Error("Audio", "Can't load music. Path : " + path);
        return Music{UNVALID};
    }

    // Put the music in the list 
    Index id;
    if (m_musicAvaiableIndex.empty()) {
        id = m_nextMusicID;
        m_nextMusicID++;
    }else{
        id = m_musicAvaiableIndex.top();
        m_musicAvaiableIndex.pop();
    }
    m_listMusic[id] = mixMusic;
    Music music{id};

    // Return the music ID
    return music;
}

Sound Audio::LoadSound(const std::string& path) {
    // Load sound
    Mix_Chunk* mixSound = Mix_LoadWAV(path.c_str());

    // Check if the music has been loaded successfully
    if (!mixSound) {
        GetLogger().Error("Audio", "Can't load sound. Path : " + path);
        return Sound{UNVALID};
    }

    // Put the music in the list 
    Index id;
    if (m_soundAvaiableIndex.empty()) {
        id = m_nextSoundID;
        m_nextSoundID++;
    }else{
        id = m_soundAvaiableIndex.top();
        m_soundAvaiableIndex.pop();
    }
    m_listSound[id] = mixSound;
    Sound sound{id};

    // Return the music ID
    return sound;
}

void Audio::FreeMusic(Music music) {
    // Check if the music is valid
    if (MusicValidity(music)) {
        // Free the music
        Mix_FreeMusic(m_listMusic[music.id]);

        // Put the index as avaiable
        m_musicAvaiableIndex.push(music.id);

        // Clear the entry
        m_listMusic[music.id] = nullptr;
    }
}

void Audio::FreeSound(Sound sound) {
    // Check if the sound is valid
    if (SoundValidity(sound)) {
        // Free the music
        Mix_FreeChunk(m_listSound[sound.id]);

        // Put the index as avaiable
        m_soundAvaiableIndex.push(sound.id);

        // Clear the entry
        m_listSound[sound.id] = nullptr;
    }
}

bool Audio::MusicValidity(Music music) {
    return m_listMusic.find(music.id) != m_listMusic.end() and m_listMusic[music.id];
}

bool Audio::SoundValidity(Sound sound) {
    return m_listSound.find(sound.id) != m_listSound.end() and m_listSound[sound.id];
}

void Audio::PlayMusic(Music music, int32_t loop) {
    Mix_PlayMusic(m_listMusic[music.id], loop);
}

void Audio::PlayFadeMusic(Music music, int32_t time, int32_t loop) {
    Mix_FadeInMusic(m_listMusic[music.id], loop, time);
}

void Audio::VolumeMusic(float volume) const {
    Mix_VolumeMusic(volume*128);
}

void Audio::PauseMusic() const {
    Mix_PauseMusic();
}

bool Audio::IsMusicPlaying() const {
    return Mix_PlayingMusic();
}

void Audio::ResumeMusic() const {
    Mix_ResumeMusic();
}

void Audio::StopFadeMusic(int time) const {
    Mix_FadeOutMusic(time);
}

void Audio::StopMusic() const {
    Mix_HaltMusic();
}

void Audio::PlaySound(Sound sound, int channel, int loop) {
    Mix_PlayChannel(channel, m_listSound[sound.id], loop);
}

void Audio::PlayFadeSound(Sound sound, int time, int channel, int loop) {
    Mix_FadeInChannel(channel, m_listSound[sound.id], loop, time);
}

void Audio::VolumeSound(Sound sound, float volume) {
    Mix_VolumeChunk(m_listSound[sound.id], volume*128);
}

}