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

#ifndef ORA_MAX_MUSIC
#define ORA_MAX_MUSIC 128
#endif

#ifndef ORA_MAX_SOUND
#define ORA_MAX_SOUND 512
#endif

class AudioManager {
public:
    AudioManager(int32_t mix_flags, int32_t frequency, uint16_t format, int32_t channels, int32_t chunk_size);

    ~AudioManager();

    int32_t load_music(const std::string& path);

    bool free_music(int32_t index);

    Music* get_music(int32_t index);

    bool valid_music(int32_t index);

    int32_t load_sound(const std::string& path);

    bool free_sound(int32_t index);

    Sound* get_sound(int32_t index);

    bool valid_sound(int32_t index);

private:
    ObjectPool<Music, ORA_MAX_MUSIC> m_musics;

    ObjectPool<Sound, ORA_MAX_SOUND> m_sounds;
};

}