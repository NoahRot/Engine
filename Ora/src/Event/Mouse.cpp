#include "Event/Mouse.hpp"

namespace ora {

Mouse::Mouse() {
    m_button_down.fill(false);
    m_button_press.fill(false);
    m_button_up.fill(false);
}

bool Mouse::button_down(MouseButton button) const {
    return m_button_down[button];
}

bool Mouse::button_up(MouseButton button) const {
    return m_button_up[button];
}

bool Mouse::button_press(MouseButton button) const {
    return m_button_press[button];
}

int32_t Mouse::mouse_x() const {
    return m_mouse_x;
}

int32_t Mouse::mouse_y() const {
    return m_mouse_y;
}

void Mouse::mouse_position(int32_t& x, int32_t& y) const {
    x = m_mouse_x;
    y = m_mouse_y;
}

void Mouse::reset() {
    SDL_GetMouseState(&m_mouse_x, &m_mouse_y);

    m_button_down.fill(false);
    m_button_up.fill(false);
}

void Mouse::manage_down(uint8_t button) {
    m_button_down[button] = true;
    m_button_press[button] = true;
}

void Mouse::manage_up(uint8_t button) {
    m_button_up[button] = true;
    m_button_press[button] = false;
}

}