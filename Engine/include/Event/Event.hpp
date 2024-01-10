#pragma once

#include <array>
#include <iostream>

#include <External/SDL2/SDL.h>

#include "Event/Keyboard.hpp"
#include "Event/Mouse.hpp"

namespace eng {

class Keyboard;
class Mouse;

class Event {
public:
    ~Event();

    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;

    static Event& Instance();

    void Manage();

    void Quit() { m_quit = true; }

    bool IsQuitting() const;

private:
    Event();

    bool m_quit;

    Keyboard& m_keyboard;
    Mouse& m_mouse;
};

Event& GetEvent();

}