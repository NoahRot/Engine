#pragma once

#include <inttypes.h>

#include <SDL2/SDL_mixer.h>

#include "Log/Logger.hpp"
#include "Engine/UniqueIndex.hpp"
#include "Memory/ContinuousVector.hpp"

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

}