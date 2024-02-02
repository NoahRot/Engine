#pragma once

#include <iostream>
#include <inttypes.h>
#include <string>

#include <External/SDL2/SDL.h>
#include <External/SDL2/SDL_mixer.h>

namespace eng {

/// @brief A structure that contain the information for the configuration of the engine
struct Configuration
{
    // SDL2
    uint32_t sdl_sdlFlags = SDL_INIT_EVERYTHING;

    // SDL Mixer
    int32_t mix_flags = MIX_INIT_FLAC|MIX_INIT_MOD|MIX_INIT_MP3|MIX_INIT_OGG|MIX_INIT_MID|MIX_INIT_OPUS;
    int32_t mix_frequency = 22050;
    uint16_t mix_format = 0x8010;
    int32_t mix_channels = 2;
    int32_t mix_chunksize = 1024;

    // Logger
    uint32_t log_initialLength = 128;
    bool log_displayCMD = true;
    bool log_displayTXT = false;
    std::string log_displayTXTName = "LogFile";

    // Window
    uint32_t win_width = 960;
    uint32_t win_height = 480;
    std::string win_name = "UNKNOW";

    // Timer
    uint32_t tim_fps = 60;
};

}