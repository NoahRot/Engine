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

    static Mouse& instance();

    bool mouse_down(MouseButton button) const;
    bool mouse_up(MouseButton button) const;
    bool mouse_press(MouseButton button) const;

    int32_t mouse_x();
    int32_t mouse_y();

    void mouse_position(int32_t& x, int32_t& y);

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