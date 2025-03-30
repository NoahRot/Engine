#include "Time/TimePoint.hpp"

namespace ora {

void TimePoint::set_delta_time(float delta_time) {
    m_delta_time = delta_time;
}

void TimePoint::reset() {
    m_start_point = std::chrono::high_resolution_clock::now();
}

bool TimePoint::has_passed() {
    auto now = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(now - m_start_point).count();

    if (elapsed_time >= m_delta_time) {
        m_start_point = now;
        return true;
    }else{
        return false;
    }
}

}