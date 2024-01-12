#include "Event/Mouse.hpp"

namespace eng {

Mouse::Mouse() {
    m_mouseDown.fill(false);
    m_mousePress.fill(false);
    m_mouseUp.fill(false);
}

Mouse& Mouse::Instance() {
    static Mouse s_instance;
    return s_instance;
}

bool Mouse::MouseDown(MouseButton button) const { return m_mouseDown[button]; }
bool Mouse::MouseUp(MouseButton button) const { return m_mouseUp[button]; }
bool Mouse::MousePress(MouseButton button) const { return m_mousePress[button]; }

int32_t Mouse::MouseX() { return m_mouseX; }
int32_t Mouse::MouseY() { return m_mouseY; }

void Mouse::MousePosition(int32_t& x, int32_t& y) { x = m_mouseX; y = m_mouseY; }

}