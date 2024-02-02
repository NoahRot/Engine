#include "Audio/Music.hpp"

namespace eng::_intern_ {

Music::Music()
:m_music(nullptr)
{}

Music::~Music() {
    if (m_music) {
        Mix_FreeMusic(m_music);
    }
}

bool Music::Load(const std::string& path) {
    // Check if a music is already loaded
    if (m_music) {
        GetLogger().Error("Music", "Music already loaded. Can't overwrite a music");
        return false;
    }

    // Load the music
    m_music = Mix_LoadMUS(path.c_str());

    // Check if the music has been loaded successfully
    if (!m_music) {
        GetLogger().Error("Music", "Can't load music. Path : " + path);
        return false;
    }

    return true;
}

bool Music::IsValid() const {
    return m_music;
}

Mix_Music* Music::GetMusic() const {
    return m_music;
}
    
}