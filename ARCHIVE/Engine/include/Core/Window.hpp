#pragma once

#include <iostream>

#include <External/SDL2/SDL.h>

#include "Core/CoreFnc.hpp"
#include "Logger/Logger.hpp"

namespace eng {

class Window {
public:
    /// @brief Destructor
    ~Window();

    // Those methods are deleted because Window is a singleton class
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    /// @brief Obtain the instance of Window
    /// @return The instance of Window
    static Window& instance();

    /// @brief Present the new frame. The window buffers are swap and
    /// the new frame is shown.
    void present();

    /// @brief Get the width of the window
    /// @return The width of the window
    uint32_t get_width();

    /// @brief Get the height of the window
    /// @return The height of the window
    uint32_t get_height();

private:
    /// @brief Constructor
    Window();

    /// @brief The SDL instance of the window
    SDL_Window* m_window;

    /// @brief The OpenGL context
    SDL_GLContext m_context;

    /// @brief The title of the window
    std::string m_title;

    /// @brief The width of the window
    uint32_t m_width;

    /// @brief The height of the window
    uint32_t m_height;
};

}