#include "Event/Event.hpp"

namespace ora {

Event::Event()
: m_quit(false)
{
    Logger::instance().log(Info, "Event created");
}

Event::~Event() {
    Logger::instance().log(Info, "Event destroyed");
}

void Event::manage() {
    // Reset events
    m_keyboard.reset();
    m_mouse.reset();

    // Poll events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_quit = true;
                break;

            case SDL_KEYDOWN:
                m_keyboard.manage_down(event.key.keysym.scancode);
                break;

            case SDL_KEYUP:
                m_keyboard.manage_up(event.key.keysym.scancode);
                break;

            case SDL_MOUSEBUTTONDOWN:
                m_mouse.manage_down(event.button.button - 1);
                break;

            case SDL_MOUSEBUTTONUP:
                m_mouse.manage_up(event.button.button - 1);
                break;
        }
    }
}

bool Event::is_quitting() const {
    return m_quit;
}

void Event::quit() {
    m_quit = true;
}

const Keyboard& Event::keyboard() const {
    return m_keyboard;
}

const Mouse& Event::mouse() const {
    return m_mouse;
}

}