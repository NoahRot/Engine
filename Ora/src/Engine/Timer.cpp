#include "Engine/Timer.hpp"

namespace ora {

Timer::Timer(uint32_t fps)
: m_last_frame(0)
{
    m_fps = fps;
    m_millisecond_per_frame = 1000/m_fps;
}

uint32_t Timer::get_delta_time() {
    return m_millisecond_per_frame;
}

uint32_t Timer::get_fps() {
    return m_fps;
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

    // Set the new frame time
    m_last_frame = current_tick;

    // Wait for the remain time
    if (time_remain > 0){
        SDL_Delay(time_remain);
    }
}

}