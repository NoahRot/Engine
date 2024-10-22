#pragma once

#include <array>

#include <SDL2/SDL.h>

namespace ora {

class Keyboard {
public:
    Keyboard();

    bool key_down(SDL_Scancode code) const;

    bool key_up(SDL_Scancode code) const;

    bool key_press(SDL_Scancode code) const;

    void reset();

    void manage_down(SDL_Scancode code);

    void manage_up(SDL_Scancode code);

private:
    std::array<bool, SDL_NUM_SCANCODES> m_key_down;
    std::array<bool, SDL_NUM_SCANCODES> m_key_up;
    std::array<bool, SDL_NUM_SCANCODES> m_key_press;
};

}