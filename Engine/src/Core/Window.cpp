#include "Core/Window.hpp"

namespace eng {

Window::Window()
: m_window(nullptr)
{
    eng::log::Logger& logger = eng::GetLogger();

    // Check if the engine has been configure
    if(!eng::IsConfigure()) {
        logger.Fatal("Window", "Engine is not configure");
        exit(EXIT_FAILURE);
    }

    // Configure Window
    eng::Configuration config = eng::GetConfiguration();
    m_title = config.win_name;
    m_width = config.win_width;
    m_height = config.win_height;

    // Create the window
    m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_OPENGL);
    if (!m_window) {
        logger.Fatal("Window", "Can't create the window");
        exit(EXIT_FAILURE);
    }

    // Create the opengl context
    m_context = SDL_GL_CreateContext(m_window);
    if (m_context == nullptr) {
        logger.Fatal("Window", "Can't create OpenGL context");
        exit(EXIT_FAILURE);
    }

    // Init GLAD
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        logger.Fatal("Window", "Can't init GLAD");
        exit(EXIT_FAILURE);
    }

    // Tell OpenGL where the left bottom corner is and what the dimensions of the windows are
    glViewport(0, 0, m_width, m_height);

    // Set the clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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