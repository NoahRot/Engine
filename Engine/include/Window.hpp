#pragma once

#include <inttypes.h>

#include <SDL2/SDL.h>

namespace eng {

class Window {
public:

private:
    SDL_Window* m_window;
    SDL_GLContext* m_context;

    uint32_t m_width;
    uint32_t m_height;
};

}