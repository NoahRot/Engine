#pragma once

#include <iostream>

#include "Core/Configuration.hpp"
#include "Core/CoreFnc.hpp"

namespace eng {

/// @brief A class to manage the time. To wait until the next frame.
class Timer {
public:
    /// @brief Destructor
    ~Timer();

    // Those methods are deleted because Timer is a singleton class
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;

    /// @brief Obtain the instance of Timer
    /// @return The instance of Timer
    static Timer& Instance();

    /// @brief Get the time for each frame in millisecond
    /// @return The number of millisecond per frame
    uint32_t GetDeltaTime();

    /// @brief Get the FPS of the application
    /// @return The FPS
    uint32_t GetFPS();

    /// @brief Change the FPS of the application
    /// @param fps The new FPS
    void SetFPS(uint32_t fps);

    /// @brief A method to call at each frame. Wait until the next frame.
    void Loop();

private:
    /// @brief Constructor
    Timer();

    /// @brief The FPS of the application
    uint32_t m_fps;

    /// @brief The time per frame in millisecond
    uint32_t m_millisecondPerFrame;

    /// @brief The last frame time (in millisecond since the start of the application)
    uint32_t m_lastFrameTime;
};

}