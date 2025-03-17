#include "Audio/AudioManager.hpp"

namespace ora {

AudioManager::AudioManager(int32_t mix_flags, int32_t frequency, uint16_t format, int32_t channels, int32_t chunk_size) {
    // Init MIX
    if (Mix_Init(mix_flags) != mix_flags) {
        std::string sdl_error(Mix_GetError());
        Mix_Quit();
        Logger::instance().log(Info, "Can not initialize MIX. Mix ERROR : " + sdl_error);
        exit(EXIT_FAILURE);
    }
    Logger::instance().log(Info, "MIX initialize");

    // Open Audio
    if (Mix_OpenAudio(frequency, format, channels, chunk_size) < 0) {
        std::string sdl_error(Mix_GetError());
        Mix_CloseAudio();
        Mix_Quit();
        Logger::instance().log(Info, "Can not open audio. Mix ERROR : " + sdl_error);
        exit(EXIT_FAILURE);
    }
    Logger::instance().log(Info, "Audio open");

    Logger::instance().log(Info, "Audio manager created");
}

AudioManager::~AudioManager() {

    // Free all music, before quitting Mix
    for (int32_t i(0) ; i < ORA_MAX_MUSIC ; ++i) {
        if (m_musics.validity(i)) {
            m_musics.remove(i);
        }
    }

    // Free all sound, before quitting Mix
    for (int32_t i(0) ; i < ORA_MAX_SOUND ; ++i) {
        if (m_sounds.validity(i)) {
            m_sounds.remove(i);
        }
    }

    // Close audio and quit mix
    Mix_CloseAudio();
    Mix_Quit();

    Logger::instance().log(Info, "Audio manager destroyed");
}

int32_t AudioManager::load_music(const std::string& path) {
    // Load the music
    Mix_Music* music = Mix_LoadMUS(path.c_str());

    // Check if the music has been loaded successfully
    if (!music) {
        Logger::instance().log(Error, "Can not load music. Music path : " + path + ". Mix Error : " + std::string(Mix_GetError()));
        return -1;
    }

    // Add to vector
    int32_t id = m_musics.add(music);
    if (id < 0) {
        Logger::instance().log(Error, "Can not add music to the pool. Number of free elements : " + std::to_string(m_musics.nbr_free_elements()));
        Mix_FreeMusic(music);
    }

    return id;
}

bool AudioManager::free_music(int32_t index) {
    return m_musics.remove(index);
}

Music* AudioManager::get_music(int32_t index) {
    return &m_musics.get(index);
}

bool AudioManager::valid_music(int32_t index) {
    return m_musics.validity(index);
}

int32_t AudioManager::load_sound(const std::string& path) {
    // Load the sound
    Mix_Chunk* sound = Mix_LoadWAV(path.c_str());

    // Check if the sound has been loaded successfully
    if (!sound) {
        Logger::instance().log(Error, "Can not load sound. Sound path : " + path + ". Mix Error : " + std::string(Mix_GetError()));
        return -1;
    }

    // Add to vector
    int32_t id = m_sounds.add(sound);
    if (id < 0) {
        Logger::instance().log(Error, "Can not add music to the pool. Number of free elements : " + std::to_string(m_musics.nbr_free_elements()));
        Mix_FreeChunk(sound);
    }

    return id;
}

bool AudioManager::free_sound(int32_t index) {
    return m_sounds.remove(index);
}

Sound* AudioManager::get_sound(int32_t index) {
    return &m_sounds.get(index);
}

bool AudioManager::valid_sound(int32_t index) {
    return m_sounds.validity(index);
}

}