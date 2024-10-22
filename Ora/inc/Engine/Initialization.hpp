#pragma once

#include <string>
#include <inttypes.h>

#include <SDL2/SDL.h>

namespace ora {

struct InitializationList
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

};

}