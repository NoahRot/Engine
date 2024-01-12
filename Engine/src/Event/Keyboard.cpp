#include "Event/Keyboard.hpp"

namespace eng {

Keyboard::Keyboard(){
    m_keyDown.fill(false);
    m_keyUp.fill(false);
    m_keyPress.fill(false);
}

Keyboard& Keyboard::Instance() {
    static Keyboard s_instance;
    return s_instance;
}

bool Keyboard::KeyDown(SDL_Scancode code) const { return m_keyDown[code]; }
bool Keyboard::KeyUp(SDL_Scancode code) const { return m_keyUp[code]; }
bool Keyboard::KeyPress(SDL_Scancode code) const { return m_keyPress[code]; }

}