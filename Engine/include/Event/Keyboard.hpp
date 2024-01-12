#pragma once

#include <array>

#include <External/SDL2/SDL.h>

#include "Event/Event.hpp"

namespace eng {

class Event;

class Keyboard {
public:
    Keyboard(const Keyboard&) = delete;
    Keyboard& operator=(const Keyboard&) = delete;

    static Keyboard& Instance();

    bool KeyDown(SDL_Scancode code) const;
    bool KeyUp(SDL_Scancode code) const;
    bool KeyPress(SDL_Scancode code) const;

private:
    friend Event;

    Keyboard();

    std::array<bool, SDL_NUM_SCANCODES> m_keyDown;
    std::array<bool, SDL_NUM_SCANCODES> m_keyUp;
    std::array<bool, SDL_NUM_SCANCODES> m_keyPress;
};

}