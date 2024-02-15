#include "Audio/Music.hpp"

namespace eng {

Music::Music()
: m_valid(false), m_index(eng::_intern_::Audio::Instance().GetMusicIndex()), m_music(nullptr)
{
    eng::_intern_::Audio::Instance().AddMusic(this);
}

Music::~Music() {
    if (m_music) {
        Mix_FreeMusic(m_music);
    }
    std::cout << "DEBUG : MUSIC DESTROYED" << std::endl;
}

bool Music::Load(const std::string& path) {
    // Check if a music has already been loaded
    if (m_valid) {
        eng::GetLogger().Error("Music", "Data already loaded. Can't overwrite data.");
        return false;
    }

    // Load the music
    m_music = Mix_LoadMUS(path.c_str());

    // Check if the music has been loaded successfully
    if (!m_music) {
        m_valid = false;
        return false;
    }
    m_valid = true;

    // Return the validity
    return m_valid;
}

bool Music::IsValid() const {
    return m_valid;
}

Index Music::GetIndex() const {
    return m_index;
}

void Music::Play(int32_t loop) const {
    Mix_PlayMusic(m_music, loop);
}

void Music::PlayFade(int32_t time, int32_t loop) const {
    Mix_FadeInMusic(m_music, loop, time);
}

void Music::Volume(float volume) {
    Mix_VolumeMusic(volume*128);
}

void Music::Pause() {
    Mix_PauseMusic();
}

bool Music::IsPlaying() {
    return Mix_PlayingMusic();
}

void Music::Resume() {
    Mix_ResumeMusic();
}

void Music::Stop() {
    Mix_HaltMusic();
}

void Music::StopFade(int32_t time) {
    Mix_FadeOutMusic(time);
}

}