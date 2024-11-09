#pragma once

#include "Window/Window.hpp"

#include "mat/Math.hpp"

namespace ora {

class Camera2D {
public:
    Camera2D(Window* window, bool rotate) 
    :   m_orthographic(mat::orthographic3<float>(0.0f, window->get_width(), 0.0f, window->get_height(), 1.0f, -1.0f)), 
        m_position({0.0f, 0.0f, 0.0f}),
        m_centre({0.5f*window->get_width(), 0.5f*window->get_height(), 0.0f}),
        m_rotation(0.0f),
        m_rotate(rotate)
    {}

    void set_position(const mat::Vec3f& position) {
        m_position = position;
    }

    void move(const mat::Vec3f& displacement) {
        m_position += displacement;
    }

    mat::Vec3f get_position() const {
        return m_position;
    }

    void set_rotation(float angle) {
        m_rotation = angle;
    }

    void rotate(float rotation) {
        m_rotation += rotation;
    }

    void enable_rotation(bool rotate) {
        m_rotate = rotate;
    }

    float get_rotation() const {
        return m_rotation;
    }

    mat::Mat4f get_proj() const {
        return m_orthographic;
    }

    mat::Mat4f get_view() const {
        if (m_rotate) {
            return mat::dot(mat::translate3<float>(m_position + m_centre), mat::rotateZ<float>(m_rotation));
        }else{
            return mat::translate3<float>(m_position + m_centre);
        }
    }

    mat::Mat4f get_view_proj() const {
        return mat::dot(m_orthographic, get_view());
    }

private:
    mat::Mat4f m_orthographic;
    mat::Vec3f m_position;
    mat::Vec3f m_centre;
    float m_rotation;
    bool m_rotate;
};

}