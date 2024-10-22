#include "Window/Window.hpp"

namespace ora {

Window::Window(uint32_t width, uint32_t height, std::string title, uint32_t sdl_flags, uint32_t win_flags, Logger* logger) 
: m_width(width), m_height(height), m_title(title), m_window(nullptr)
{
    // Init SDL
    if (SDL_Init(sdl_flags) != 0) {
        SDL_Quit();
        logger->log(ora::Fatal, "Can not initialize SDL");
        exit(EXIT_FAILURE);
    }
    logger->log(ora::Info, "SDL initialize");

    // Set Attribute for OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // Use version 4.1 of OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1); // Use version 4.1 of OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // Disable old functions
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true); // Set double buffering
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Create SDL window
    m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, win_flags);
    if (!m_window) {
        logger->log(ora::Fatal, "Can not create SDL window");
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // Create the opengl context
    m_context = SDL_GL_CreateContext(m_window);
    if (m_context == nullptr) {
        logger->log(ora::Fatal, "Can not create OpenGL context");
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    logger->log(ora::Info, "SDL Window and OpenGL context created");

    // Init GLAD
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        logger->log(ora::Fatal, "Can not init GLAD");
        SDL_GL_DeleteContext(m_context);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    logger->log(ora::Info, "GLAD initialize");

    // Tell OpenGL where the left bottom corner is and what the dimensions of the windows are
    glViewport(0, 0, m_width, m_height);

    // Set the clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    logger->log(ora::Info, "Window created");
}

Window::~Window() {
    // Destroy window
    if(m_window) {
        SDL_DestroyWindow(m_window);
    }

    // Destroy OpenGl context
    if(m_context) {
        SDL_GL_DeleteContext(m_context);
    }

    // Quit SDL
    SDL_Quit();
}

uint32_t Window::get_width() const {
    return m_width;
}

uint32_t Window::get_height() const {
    return m_height;
}

void Window::present() const {
    SDL_GL_SwapWindow(m_window);
}

}