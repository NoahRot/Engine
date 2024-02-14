#include "Audio/Sound.hpp"

namespace eng {

Sound::Sound()
: m_valid(false), m_index(eng::_intern_::Audio::Instance().GetSoundIndex()), m_sound(nullptr)
{
    eng::_intern_::Audio::Instance().AddSound(this);
}

Sound::~Sound() {
    eng::_intern_::Audio::Instance().RemoveSound(this);
    if (m_sound) {
        Mix_FreeChunk(m_sound);
    }
    std::cout << "DEBUG : SOUND DESTROYED" << std::endl;
}

bool Sound::Load(const std::string& path) {
    // Load the music
    m_sound = Mix_LoadWAV(path.c_str());

    // Check if the music has been loaded successfully
    if (!m_sound) {
        m_valid = false;
        return false;
    }
    m_valid = true;

    // Return the validity
    return m_valid;
}

bool Sound::IsValid() const {
    return m_valid;
}

Index Sound::GetIndex() const {
    return m_index;
}

void Sound::Play(int channel, int loop) {
    Mix_PlayChannel(channel, m_sound, loop);
}

void Sound::PlayFade(int time, int channel, int loop) {
    Mix_FadeInChannel(channel, m_sound, loop, time);
}
void Sound::Volume(float volume) {
    Mix_VolumeChunk(m_sound, volume*128);
}

}