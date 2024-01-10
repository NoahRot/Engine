#include "Event/Event.hpp"

namespace eng {

Event& GetEvent() {
    return Event::Instance();
}



Event::Event()
: m_quit(false), m_keyboard(Keyboard::Instance()), m_mouse(Mouse::Instance())
{
    std::cout << "DEBUG : Event created" << std::endl;
}

Event::~Event() {
    std::cout << "DEBUG : Event destroyed" << std::endl;
}

Event& Event::Instance() {
    static Event s_instance;
    return s_instance;
}

void Event::Manage() {
    // Fill down and up with false
    m_keyboard.m_keyDown.fill(false);
    m_keyboard.m_keyUp.fill(false);

    m_mouse.m_mouseDown.fill(false);
    m_mouse.m_mouseUp.fill(false);

    // Mouse position
    SDL_GetMouseState(&m_mouse.m_mouseX, &m_mouse.m_mouseY);

    // Manage event
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type)
        {
        case SDL_QUIT:
            m_quit = true;
            break;
        case SDL_KEYDOWN:
            m_keyboard.m_keyDown[event.key.keysym.scancode] = true;
            m_keyboard.m_keyPress[event.key.keysym.scancode] = true;
            break;
        case SDL_KEYUP:
            m_keyboard.m_keyUp[event.key.keysym.scancode] = true;
            m_keyboard.m_keyPress[event.key.keysym.scancode] = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            m_mouse.m_mouseDown[event.button.button - 1] = true;
            m_mouse.m_mousePress[event.button.button - 1] = true;
            break;
        case SDL_MOUSEBUTTONUP:
            m_mouse.m_mouseUp[event.button.button - 1] = true;
            m_mouse.m_mousePress[event.button.button - 1] = false;
            break;
        }
    }
}

bool Event::IsQuitting() const {
    return m_quit;
}

}