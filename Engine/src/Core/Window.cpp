#include "Core/Window.hpp"

namespace eng {

Window::Window(uint32_t width, uint32_t height)
: m_window(nullptr), m_context(nullptr), m_width(width), m_height(height)
{
    m_window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_SHOWN);
    if (!m_window) {
        std::cout << "WINDOW ERROR" << std::endl;
    }
}

Window::~Window() {
    if(m_window) {
        SDL_DestroyWindow(m_window);
    }

    if(m_context) {
        SDL_GL_DeleteContext(m_context);
    }
}
    
}