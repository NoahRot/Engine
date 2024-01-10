#pragma once

#include <iostream>
#include <inttypes.h>
#include <string>

#include <External/SDL2/SDL.h>

namespace eng {

/// @brief A structure that contain the information for the configuration of the engine
struct Configuration
{
    // SDL2
    Uint32 sdl_sdlFlags = SDL_INIT_EVERYTHING;

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