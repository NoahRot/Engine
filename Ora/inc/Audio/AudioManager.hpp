#pragma once

#include <inttypes.h>

#include <SDL2/SDL_mixer.h>

#include "Log/Logger.hpp"
#include "Engine/UniqueIndex.hpp"
#include "Memory/ContinuousVector.hpp"
#include "Audio/Music.hpp"
#include "Audio/Sound.hpp"
#include "Memory/ObjectPool.hpp"

namespace ora {

class AudioManager
{
public:
    AudioManager(int32_t mix_flags, int32_t frequency, uint16_t format, int32_t channels, int32_t chunk_size);

    ~AudioManager();

    uint32_t load_music(const std::string& file_path);

    uint32_t load_sound(const std::string& file_path);

    void free_music(uint32_t id);

    void free_sound(uint32_t id);

    void play_music(uint32_t id, int32_t loop = 0);

    void play_fade_music(uint32_t id, int32_t time, int32_t loop = 0);

    void volume_music(float volume);

    void pause_music();

    bool is_playing_music();

    bool is_paused_music();

    void resume_music();

    void stop_music();

    void stop_fade_music(int32_t time);

    void volume_sound(uint32_t id, float volume);

    void play_sound(uint32_t id, int channel = -1, int loop = 0);

    void play_fade_sound(uint32_t id, int time, int channel = -1, int loop = 0);

private:
    VectorContinuous<Mix_Music*> m_music;

    VectorContinuous<Mix_Chunk*> m_sound;
};

#ifndef ORA_MAX_MUSIC
#define ORA_MAX_MUSIC 128
#endif

#ifndef ORA_MAX_SOUND
#define ORA_MAX_SOUND 512
#endif

class AudioManager_ {
public:
    AudioManager_(int32_t mix_flags, int32_t frequency, uint16_t format, int32_t channels, int32_t chunk_size) {
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

    ~AudioManager_() {
        // Free musics
        for (uint32_t i(0) ; i < ORA_MAX_MUSIC ; ++i) {
            if (m_musics.validity(i)) {
                Music& music = m_musics.get(i);
                music.~Music();
            }
        }

        // Free sounds
        for (uint32_t i(0) ; i < ORA_MAX_SOUND ; ++i) {
            if (m_sounds.validity(i)) {
                Sound& sound = m_sounds.get(i);
                sound.~Sound();
            }
        }

        // Close audio and quit mix
        Mix_CloseAudio();
        Mix_Quit();

        Logger::instance().log(Info, "Audio manager destroyed");
    }

    int32_t load_music(const std::string& path);

    bool free_music(int32_t index);

    Music& get_music(int32_t index);

    int32_t load_sound(const std::string& path);

    bool free_sound(int32_t index);

    Sound& get_sound(int32_t index);

private:
    ObjectPool<Music, ORA_MAX_MUSIC> m_musics;

    ObjectPool<Sound, ORA_MAX_SOUND> m_sounds;
};

}