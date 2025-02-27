#include "Core/Timer.hpp"

namespace eng {

Timer::Timer()
: m_last_frame(0)
{
    Configuration config = eng::get_configuration();

    m_fps = config.tim_fps;
    m_millisecond_per_frame = 1000/m_fps;

    std::cout << "DEBUG : Timer created" << std::endl;
}

Timer::~Timer() {
    std::cout << "DEBUG : Timer destroyed" << std::endl;
}

Timer& Timer::instance() {
    static Timer s_instance;
    return s_instance;
}

uint32_t Timer::get_delta_time() {
    return m_millisecond_per_frame;
}

uint32_t Timer::get_fps() {
    return m_fps;
}

uint32_t Timer::get_last_frame_duration() {
    return m_last_frame_duration;
}

void Timer::set_fps(uint32_t fps) {
    m_fps = fps;
    m_millisecond_per_frame = 1000/m_fps;
}

void Timer::loop() {
    // Get current tick since the beginning of the application
    int32_t current_tick = SDL_GetTicks();

    // Compute the remained time
    int32_t time_remain(m_last_frame + m_millisecond_per_frame - current_tick );

    // Set duration of the last frame
    m_last_frame_duration = current_tick - m_last_frame;

    // Set the new frame time
    m_last_frame = current_tick;

    // End point time
    m_total_frame_point.end_point();

    // Wait for the remain time
    if (time_remain > 0){
        SDL_Delay(time_remain);
    }

    // Start point time
    m_total_frame_point.start_point();
}

void Timer::create_point(const std::string& name) {
    m_map_time_point[name] = TimePoint();
}

void Timer::start_point(const std::string& name) {
    m_map_time_point[name].start_point();
}

void Timer::end_point(const std::string& name) {
    m_map_time_point[name].end_point();
}

float Timer::get_mean_delta_point(const std::string& name) {
    return m_map_time_point[name].get_mean_delta();
}

std::unordered_map<std::string, Timer::TimePoint> Timer::get_map_time_point() {
    return m_map_time_point;
}

Timer::TimePoint Timer::get_total_frame_point() {
    return m_total_frame_point;
}

}