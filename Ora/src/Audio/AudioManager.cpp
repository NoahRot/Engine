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
    // Free musics
    for (auto i : m_music) {
        if (i) {
            Mix_FreeMusic(i);
        }
    }

    // Free sounds
    for (auto i : m_sound) {
        if (i) {
            Mix_FreeChunk(i);
        }
    }

    // Close audio and quit mix
    Mix_CloseAudio();
    Mix_Quit();

    Logger::instance().log(Info, "Audio manager destroyed");
}

uint32_t AudioManager::load_music(const std::string& file_path) {
    // Load the music
    Mix_Music* music = Mix_LoadMUS(file_path.c_str());

    // Check if the music has been loaded successfully
    if (!music) {
        Logger::instance().log(Info, "Can not load music. Music path : " + file_path + ". Mix Error : " + std::string(Mix_GetError()));
        return UNVALID_32;
    }

    // Add to vector
    uint32_t id = m_music.add(music);
    return id;
}

uint32_t AudioManager::load_sound(const std::string& file_path) {
    // Load the sound
    Mix_Chunk* sound = Mix_LoadWAV(file_path.c_str());

    // Check if the sound has been loaded successfully
    if (!sound) {
        Logger::instance().log(Info, "Can not load sound. Sound path : " + file_path + ". Mix Error : " + std::string(Mix_GetError()));
        return UNVALID_32;
    }

    // Add to vector
    uint32_t id = m_sound.add(sound);
    return id;
}

void AudioManager::free_music(uint32_t id) {
    Mix_FreeMusic(m_music[id]);
    m_music[id] = nullptr;

    m_music.remove(id);
}

void AudioManager::free_sound(uint32_t id) {
    Mix_FreeChunk(m_sound[id]);
    m_sound[id] = nullptr;

    m_sound.remove(id);
}

void AudioManager::play_music(uint32_t id, int32_t loop) {
    Mix_PlayMusic(m_music[id], loop);
}

void AudioManager::play_fade_music(uint32_t id, int32_t time, int32_t loop) {
    Mix_FadeInMusic(m_music[id], loop, time);
}

void AudioManager::volume_music(float volume) {
    Mix_VolumeMusic(volume*128);
}

void AudioManager::pause_music() {
    Mix_PauseMusic();
}

bool AudioManager::is_playing_music() {
    return Mix_PlayingMusic();
}

bool AudioManager::is_paused_music() {
    return Mix_PausedMusic();
}

void AudioManager::resume_music() {
    Mix_ResumeMusic();
}

void AudioManager::stop_music() {
    Mix_HaltMusic();
}

void AudioManager::stop_fade_music(int32_t time) {
    Mix_FadeOutMusic(time);
}

void AudioManager::volume_sound(uint32_t id, float volume) {
    Mix_VolumeChunk(m_sound[id], volume*128);
}

void AudioManager::play_sound(uint32_t id, int channel, int loop) {
    Mix_PlayChannel(channel, m_sound[id], loop);
}

void AudioManager::play_fade_sound(uint32_t id, int time, int channel, int loop) {
    Mix_FadeInChannel(channel, m_sound[id], loop, time);
}

}