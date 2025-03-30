#pragma once

#include <inttypes.h>

#include <SDL2/SDL_mixer.h>

#include "Log/Logger.hpp"
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
    /// @brief Constructor
    /// @param mix_flags Flags for SDL Mixer
    /// @param frequency Sampel frequency
    /// @param format Audio format
    /// @param channels Channels (mono or stereo)
    /// @param chunk_size Size of chunk for sample
    AudioManager(int32_t mix_flags, int32_t frequency, uint16_t format, int32_t channels, int32_t chunk_size);

    /// @brief Destructor
    ~AudioManager();

    /// @brief Load a music
    /// @param path Path of the music file
    /// @return The index of the Music. Return -1 if a problem occured
    int32_t load_music(const std::string& path);

    /// @brief Free a Music
    /// @param index Index of the music
    /// @return True if the process succed
    bool free_music(int32_t index);

    /// @brief Get a music from its index
    /// @param index Index of the music
    /// @return A pointer to the Music
    Music* get_music(int32_t index);

    /// @brief Check the validity of an Index
    /// @param index Index of the music
    /// @return True if the index is valid, False otherwise
    bool valid_music(int32_t index);

    /// @brief 
    /// @param path 
    /// @return 
    int32_t load_sound(const std::string& path);

    bool free_sound(int32_t index);

    Sound* get_sound(int32_t index);

    bool valid_sound(int32_t index);

private:
    ObjectPool<Music, ORA_MAX_MUSIC> m_musics;

    ObjectPool<Sound, ORA_MAX_SOUND> m_sounds;
};

}