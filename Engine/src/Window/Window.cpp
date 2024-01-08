#include "Window/Window.hpp"

namespace eng {

Window::Window()
{
    
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