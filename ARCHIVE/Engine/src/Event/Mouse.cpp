#include "Event/Mouse.hpp"

namespace eng {

Mouse::Mouse() {
    m_mouseDown.fill(false);
    m_mousePress.fill(false);
    m_mouseUp.fill(false);
}

Mouse& Mouse::instance() {
    static Mouse s_instance;
    return s_instance;
}

bool Mouse::mouse_down(MouseButton button) const { return m_mouseDown[button]; }
bool Mouse::mouse_up(MouseButton button) const { return m_mouseUp[button]; }
bool Mouse::mouse_press(MouseButton button) const { return m_mousePress[button]; }

int32_t Mouse::mouse_x() { return m_mouseX; }
int32_t Mouse::mouse_y() { return m_mouseY; }

void Mouse::mouse_position(int32_t& x, int32_t& y) { x = m_mouseX; y = m_mouseY; }

}