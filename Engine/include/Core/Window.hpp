#pragma once

#include <iostream>

#include <External/SDL2/SDL.h>

#include "Core/CoreFnc.hpp"
#include "Logger/Logger.hpp"

namespace eng {

class Window {
public:
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    ~Window();

    static Window& Instance();

    void Present();

    uint32_t GetWidth();

    uint32_t GetHeight();

private:
    Window();

    SDL_Window* m_window;
    SDL_GLContext m_context;

    uint32_t m_width;
    uint32_t m_height;
};

}