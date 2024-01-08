#pragma once

#include <External/SDL2/SDL.h>
#include <inttypes.h>

namespace eng {

class Window {
public:
    Window();

    ~Window();

private:
    SDL_Window* m_window;
    SDL_GLContext* m_context;

    uint32_t m_width;
    uint32_t m_height;
};

}