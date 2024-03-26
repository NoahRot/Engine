#include "Event/Keyboard.hpp"

namespace eng {

Keyboard::Keyboard(){
    m_keyDown.fill(false);
    m_keyUp.fill(false);
    m_keyPress.fill(false);
}

Keyboard& Keyboard::instance() {
    static Keyboard s_instance;
    return s_instance;
}

bool Keyboard::key_down(SDL_Scancode code) const { return m_keyDown[code]; }
bool Keyboard::key_up(SDL_Scancode code) const { return m_keyUp[code]; }
bool Keyboard::key_press(SDL_Scancode code) const { return m_keyPress[code]; }

}