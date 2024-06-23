#pragma once

#include <iostream>
#include <unordered_map>
#include <string>

#include "Core/Configuration.hpp"
#include "Core/CoreFnc.hpp"

namespace eng {

/// @brief A class to manage the time. To wait until the next frame.
class Timer {
public:

    struct TimePoint {
        uint32_t start;
        uint32_t delta_accumulator;
        uint32_t nb_passage;

        TimePoint()
        : start(0), delta_accumulator(0), nb_passage(0)
        {}

        void start_point() {
            start = SDL_GetTicks();
        }

        void end_point() {
            if (start) {
                delta_accumulator += SDL_GetTicks() - start;
                ++nb_passage;
            }
        }

        float get_mean_delta() {
            return (float)delta_accumulator / ((float)nb_passage - 1.0f);
        }
    };

public:
    /// @brief Destructor
    ~Timer();

    // Those methods are deleted because Timer is a singleton class
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;

    /// @brief Obtain the instance of Timer
    /// @return The instance of Timer
    static Timer& instance();

    /// @brief Get the time for each frame in millisecond
    /// @return The number of millisecond per frame
    uint32_t get_delta_time();

    /// @brief Get the FPS of the application
    /// @return The FPS
    uint32_t get_fps();

    /// @brief Get the duration of the last frame
    /// @return The duration of the last frame in millisecond
    uint32_t get_last_frame_duration();

    /// @brief Change the FPS of the application
    /// @param fps The new FPS
    void set_fps(uint32_t fps);

    /// @brief A method to call at each frame. Wait until the next frame.
    void loop();

    /// @brief Create a time point to evaluate the time of an operation
    /// @warning Create the time point before the main loop
    /// @param name The name of the time point
    void create_point(const std::string& name);

    /// @brief Start the timer of a time point (begining of an operation)
    /// @param name The name of the time point
    void start_point(const std::string& name);

    /// @brief End the timer of a time point (end of an operation)
    /// @param name The name of the time point
    void end_point(const std::string& name);

    /// @brief Get the mean time of an operation
    /// @param name The name of the time point
    /// @return The mean time in millisecond
    float get_mean_delta_point(const std::string& name);

    /// @brief Get the map containing all the time point
    /// @return The map of all the time point
    std::unordered_map<std::string, TimePoint> get_map_time_point();

    /// @brief Get the time point of a total frame
    /// @return The time point of the total frame
    TimePoint get_total_frame_point();

private:
    /// @brief Constructor
    Timer();

    /// @brief The FPS of the application
    uint32_t m_fps;

    /// @brief The time per frame in millisecond
    uint32_t m_millisecond_per_frame;

    /// @brief The last frame time (in millisecond since the start of the application)
    uint32_t m_last_frame;

    /// @brief Duration of the last frame in millisecond
    uint32_t m_last_frame_duration;

    /// @brief A time point that represent the total time of a frame
    TimePoint m_total_frame_point;

    /// @brief A map containing the different time point associate with a name
    std::unordered_map<std::string, TimePoint> m_map_time_point;
};

}