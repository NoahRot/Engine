#pragma once

#include <chrono>

namespace ora {

class TimePoint {
public:
    void set_delta_time(float delta_time);

    void reset();

    bool has_passed();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start_point;
    float m_delta_time;
};
        

}