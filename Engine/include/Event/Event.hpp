#pragma once

#include <array>
#include <iostream>

#include <External/SDL2/SDL.h>

#include "Event/Keyboard.hpp"
#include "Event/Mouse.hpp"
#include "Core/CoreFnc.hpp"
#include "Logger/Logger.hpp"

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

private:
    Event();

    Keyboard& m_keyboard;
    Mouse& m_mouse;
};

}