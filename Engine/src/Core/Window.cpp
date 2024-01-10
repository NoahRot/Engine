#include "Core/Window.hpp"

namespace eng {

Window& GetWindow() {
    return Window::Instance();
}



Window::Window()
: m_window(nullptr), m_context(nullptr)
{
    eng::log::Logger& logger = eng::log::GetLogger();

    // Check if the engine has been configure
    if(!eng::_intern_::IsConfigure()) {
        logger.Fatal("Window", "Engine is not configure");
        exit(EXIT_FAILURE);
    }

    eng::Configuration config = eng::_intern_::GetConfiguration();

    // Create the window
    m_window = SDL_CreateWindow(config.win_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, config.win_width, config.win_height, SDL_WINDOW_OPENGL);
    if (!m_window) {
        logger.Fatal("Window", "Can't create the window");
        exit(EXIT_FAILURE);
    }

    // [TODO] Create the opengl context

    std::cout << "DEBUG : Window created" << std::endl;
}

Window::~Window() {
    if(m_window) {
        SDL_DestroyWindow(m_window);
    }

    if(m_context) {
        SDL_GL_DeleteContext(m_context);
    }

    std::cout << "DEBUG : Window destroyed" << std::endl;
}

Window& Window::Instance() {
    static Window s_instance;
    return s_instance;
}
    
void Window::Present() {
    SDL_GL_SwapWindow(m_window);
}

uint32_t Window::GetWidth() {
    return m_width;
}

uint32_t Window::GetHeight() {
    return m_height;
}

}