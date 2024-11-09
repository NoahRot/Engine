#pragma once

#include <inttypes.h>
#include <iostream>
#include <chrono>

#include <SDL2/SDL.h>

#include "Log/Logger.hpp"

namespace ora {

class Timer {
public:
    /// @brief Constructor
    Timer(uint32_t fps);

    /// @brief Destructor
    ~Timer();

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

class Chrono {
public:
    Chrono()
    : m_accumulator(0), m_ticks(0)
    {
        m_time_point = std::chrono::high_resolution_clock::now();
    }

    void set_time_point() {
        m_time_point = std::chrono::high_resolution_clock::now();
    }

    uint32_t delta_time() {
        std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(now - m_time_point).count();
    }

    void accumulate() {
        std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
        m_accumulator += std::chrono::duration_cast<std::chrono::milliseconds>(now - m_time_point).count();
        m_ticks++;
    }

    float get_accumulate_mean() {
        return float(m_accumulator)/float(m_ticks);
    }

    void reset_accumulator() {
        m_accumulator = 0;
        m_ticks = 0;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_time_point;
    uint32_t m_accumulator;
    uint32_t m_ticks;
};

}