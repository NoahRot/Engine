#pragma once

#include "mat/Math.hpp"

namespace ora {

class Camera2D {
public:
    Camera2D(float window_width, float window_height)
    : m_zoom(1.0f), m_window_width(window_width), m_window_height(window_height)
    {
        compute_matrix();
    }

    void set_position(mat::Vec2f position) {
        m_position = position;
    }

    void move_position(mat::Vec2f displacement) {
        m_position += displacement;
    }

    void set_zoom(float zoom_) {
        m_zoom = zoom_ > 0.1f ? zoom_ : 0.1f;
        m_zoom = zoom_;
    }

    void zoom(float zoom_factor) {
        set_zoom(zoom_factor*m_zoom);
    }

    mat::Vec2f get_position() const {
        return m_position;
    }

    mat::Mat4f get_projection() const {
        return m_projection;
    }

    mat::Mat4f get_view() const {
        return m_view;
    }

    mat::Mat4f get_vp() const {
        return mat::dot(m_projection, m_view);
    }

    void compute_matrix() {
        // Orthographic projection (left, right, bottom, top)
        float half_width = (m_window_width / 2.0f) / m_zoom;
        float half_height = (m_window_height / 2.0f) / m_zoom;
        m_projection = mat::orthographic3<float>(-half_width, half_width, -half_height, half_height, -1.0f, 1.0f);

        // View Matrix (inverse transform)
        mat::Vec3f position{-m_position[0], -m_position[1], 0.0f};
        mat::Mat4f translation = mat::translate3<float>(position);
        m_view = translation;
    }

private:

    mat::Vec2f m_position;
    float m_zoom;
    float m_window_width, m_window_height;
    mat::Mat4f m_projection;
    mat::Mat4f m_view;
};

}