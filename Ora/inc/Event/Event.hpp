#pragma once

#include <SDL2/SDL.h>

#include "Event/Keyboard.hpp"
#include "Event/Mouse.hpp"
#include "Log/Logger.hpp"

namespace ora {

class Event {
public:
    Event(Logger* logger);

    void manage();

    bool is_quitting() const;

    void quit();

    const Keyboard& keyboard() const;

    const Mouse& mouse() const;

private:
    bool m_quit;
    Keyboard m_keyboard;
    Mouse m_mouse;
};

}