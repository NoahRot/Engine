#include "Time/Chrono.hpp"

namespace ora {

Chrono::Chrono()
: m_start_point(std::chrono::high_resolution_clock::now()), m_accumulator(0), m_nbr_loop(0)
{}

void Chrono::reset() {
    m_accumulator = 0;
    m_nbr_loop = 0;
}

void Chrono::start() {
    m_start_point = std::chrono::high_resolution_clock::now(); 
}

void Chrono::end() {
    auto now = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(now - m_start_point).count();

    m_accumulator += elapsed_time;
    m_nbr_loop++;
    m_start_point = now;
}

float Chrono::get_mean_time() {
    return m_nbr_loop == 0 ? 0.0f : (float)m_accumulator/m_nbr_loop;
}

}