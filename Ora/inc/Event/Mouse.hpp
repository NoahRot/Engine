#pragma once

#include <array>

#include <SDL2/SDL.h>

namespace ora {

enum MouseButton {
    MOUSE_LEFT          = 0,
    MOUSE_MIDDLE        = 1,
    MOUSE_RIGHT         = 2,
    MOUSE_EXTRA_1       = 3,
    MOUSE_EXTRA_2       = 4,
    MOUSE_BUTTON_COUNT  = 5
};

class Mouse {
public:
    Mouse();

    bool button_down(MouseButton button) const;

    bool button_up(MouseButton button) const;

    bool button_press(MouseButton button) const;

    int32_t mouse_x() const;

    int32_t mouse_y() const;

    void mouse_position(int32_t& x, int32_t& y) const;

    void reset();

    void manage_down(uint8_t button);

    void manage_up(uint8_t button);

    void set_window_height(int32_t height);

private:
    std::array<bool, MOUSE_BUTTON_COUNT> m_button_down;
    std::array<bool, MOUSE_BUTTON_COUNT> m_button_up;
    std::array<bool, MOUSE_BUTTON_COUNT> m_button_press;

    int32_t m_mouse_x;
    int32_t m_mouse_y;

    int32_t m_window_height;
};

}