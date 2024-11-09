#pragma once

#include <string>
#include <inttypes.h>
#include <fstream>
#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

namespace ora {

struct Configuration
{
    // Logger parameters

    std::string log_file_name   = "orange.log";
    uint8_t     log_state       = 0b11111111;

    // Window parameters

    uint32_t win_width = 1920;
    uint32_t win_height = 1080;
    std::string win_title = "Orange Engine";
    uint32_t win_sdl_flags = SDL_INIT_EVERYTHING;
    uint32_t win_win_flags = SDL_WINDOW_OPENGL;

    // Timer parameter

    uint32_t tim_fps = 60;

    // Audio parameters

    int32_t aud_mix_flags = MIX_INIT_FLAC|MIX_INIT_MOD|MIX_INIT_MP3|MIX_INIT_OGG|MIX_INIT_MID|MIX_INIT_OPUS;
    int32_t aud_frequency = 22050;
    uint16_t aud_format = 0x8010;
    int32_t aud_channels = 2;
    int32_t aud_chunksize = 1024;

    // Texture parameters

    bool tex_pixel_perfect = true;
};

}