#include "Event/Keyboard.hpp"

namespace ora {

Keyboard::Keyboard() {
    m_key_down.fill(false);
    m_key_press.fill(false);
    m_key_up.fill(false);
}

bool Keyboard::key_down(SDL_Scancode code) const {
    return m_key_down[code];
}

bool Keyboard::key_up(SDL_Scancode code) const {
    return m_key_up[code];
}

bool Keyboard::key_press(SDL_Scancode code) const {
    return m_key_press[code];
}

void Keyboard::reset() {
    m_key_down.fill(false);
    m_key_up.fill(false);
}

void Keyboard::manage_down(SDL_Scancode code) {
    m_key_down[code] = true;
    m_key_press[code] = true;
}

void Keyboard::manage_up(SDL_Scancode code) {
    m_key_up[code] = true;
    m_key_press[code] = false;
}

}