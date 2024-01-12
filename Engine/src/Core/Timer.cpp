#include "Core/Timer.hpp"

namespace eng {

Timer::Timer()
: m_lastFrameTime(0)
{
    Configuration config = eng::GetConfiguration();

    m_fps = config.tim_fps;
    m_millisecondPerFrame = 1000/m_fps;

    std::cout << "DEBUG : Timer created" << std::endl;
}

Timer::~Timer() {
    std::cout << "DEBUG : Timer destroyed" << std::endl;
}

Timer& Timer::Instance() {
    static Timer s_instance;
    return s_instance;
}

uint32_t Timer::GetDeltaTime() {
    return m_millisecondPerFrame;
}

uint32_t Timer::GetFPS() {
    return m_fps;
}

void Timer::SetFPS(uint32_t fps) {
    m_fps = fps;
    m_millisecondPerFrame = 1000/m_fps;
}

void Timer::Loop() {
    // Compute the remained time
    int32_t timeRemain(m_lastFrameTime + m_millisecondPerFrame - SDL_GetTicks() );

    // Set the new frame time
    m_lastFrameTime = SDL_GetTicks();

    // Wait for the remain time
    if (timeRemain > 0){
        SDL_Delay(timeRemain);
    }
}

}