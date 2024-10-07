#pragma once

#include <string>

#include <External/SDL2/SDL.h>
#include <glad/glad.h>

#include "Logger/Log.hpp"

namespace eng {

// Window class
class Window {
public:
    /// @brief Constructor
    /// @param title Title of the window
    /// @param width Width of the window in pixel
    /// @param height Height of the window in pixel 
    Window(const std::string& title, uint32_t width, uint32_t height) 
    : m_window(nullptr), m_title(title), m_width(width), m_height(height)
    {}

    /// @brief Initialization of the window
    /// @param logger The logger class
    /// @return True if the initialization succeed
    bool init(Logger* logger) {
        // Create an SDL window
        m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_OPENGL);
        if (!m_window) {
            logger->log(ERROR, "Can not create SDL window");
            return false;
        }

        // Create the opengl context
        m_context = SDL_GL_CreateContext(m_window);
        if (m_context == NULL) {
            logger->log(ERROR, "Can not create SDL context");
            SDL_DestroyWindow(m_window);
            return false;
        }

        // Init GLAD
        if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
            logger->log(ERROR, "Can not initialize GLAD");
            SDL_GL_DeleteContext(m_context);
            SDL_DestroyWindow(m_window);
            return false;
        }

        // Tell OpenGL where the left bottom corner is and what the dimensions of the windows are
        glViewport(0, 0, m_width, m_height);

        // Set the clear color to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        return true;
    }

    /// @brief Quit window
    void quit() {
        SDL_GL_DeleteContext(m_context);
        SDL_DestroyWindow(m_window);
    }

    // Swap the buffers to present the next frame
    void present() {
        SDL_GL_SwapWindow(m_window);
    }

    /// @brief Get the width of the window
    /// @return The width of the window
    uint32_t get_width() const {
        return m_width;
    }

    /// @brief Get the height of the window
    /// @return The height of the window
    uint32_t get_height() const {
        return m_height;
    }

private:
    SDL_Window* m_window;       // SDL Window instance
    SDL_GLContext m_context;    // OpenGL context
    std::string m_title;        // Title of the window
    uint32_t m_width;           // Width of the window
    uint32_t m_height;          // Height of the window
};

}