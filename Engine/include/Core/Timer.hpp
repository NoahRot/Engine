#pragma once

#include <iostream>

#include "Core/Configuration.hpp"
#include "Core/Core.hpp"

namespace eng {

class Timer {
public:
    ~Timer();

    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;

    static Timer& Instance();

    uint32_t GetDeltaTime();

    uint32_t GetFPS();

    void Loop();

private:
    Timer();

    uint32_t m_fps;
    uint32_t m_millisecondPerFrame;
    uint32_t m_lastFrameTime;
};

Timer& GetTimer();

}