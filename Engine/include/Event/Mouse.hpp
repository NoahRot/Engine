#pragma once

#include <array>

#include <External/SDL2/SDL.h>

#include "Event/Event.hpp"

namespace eng {

class Event;

enum MouseButton {
    MouseLeft           = 0,
    MouseMiddle         = 1,
    MouseRight          = 2,
    MOUSE_EXTRA_1       = 3,
    MOUSE_EXTRA_2       = 4,
    MouseButtonCount    = 5
};

class Mouse {
public:
    Mouse(const Mouse&) = delete;
    Mouse& operator=(const Mouse&) = delete;

    static Mouse& Instance();

    bool MouseDown(MouseButton button) const;
    bool MouseUp(MouseButton button) const;
    bool MousePress(MouseButton button) const;

    int32_t MouseX();
    int32_t MouseY();

    void MousePosition(int32_t& x, int32_t& y);

private:
    friend Event;

    Mouse();

    std::array<bool, MouseButtonCount> m_mouseDown;
    std::array<bool, MouseButtonCount> m_mouseUp;
    std::array<bool, MouseButtonCount> m_mousePress;

    int32_t m_mouseX;
    int32_t m_mouseY;
};

}