#pragma once

#include <chrono>

namespace ora {

class Chrono {
public:
    Chrono();

    void reset();

    void start();

    void end();

    float get_mean_time();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start_point;

    uint32_t m_accumulator;
    uint32_t m_nbr_loop;

};

}