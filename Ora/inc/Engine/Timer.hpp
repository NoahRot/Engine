#pragma once

#include <inttypes.h>

#include <SDL2/SDL.h>

namespace ora {

class Timer {
public:
    /// @brief Constructor
    Timer(uint32_t fps);

    /// @brief Get the time for each frame in millisecond
    /// @return The number of millisecond per frame
    uint32_t get_delta_time();

    /// @brief Get the FPS of the application
    /// @return The FPS
    uint32_t get_fps();

    /// @brief Change the FPS of the application
    /// @param fps The new FPS
    void set_fps(uint32_t fps);

    /// @brief A method to call at each frame. Wait until the next frame.
    void loop();

private:
    /// @brief The FPS of the application
    uint32_t m_fps;

    /// @brief The time per frame in millisecond
    uint32_t m_millisecond_per_frame;

    /// @brief The last frame time (in millisecond since the start of the application)
    uint32_t m_last_frame;
};

}