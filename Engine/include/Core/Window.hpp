#pragma once

#include <iostream>

#include <External/SDL2/SDL.h>

namespace eng {

class Window {
public:
    Window(uint32_t width, uint32_t height);

    ~Window();

private:
    SDL_Window* m_window;
    SDL_GLContext* m_context;

    uint32_t m_width;
    uint32_t m_height;
};

}