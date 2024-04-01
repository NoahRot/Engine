#pragma once

#include "Math/Math.hpp"

namespace eng {

class Camera2D {
public:
    Camera2D(float left, float right, float bottom, float top, math::Vec3f position = math::Vec3f({0.0f, 0.0f, 0.0f}), float rotation = 0);

    void set_position(math::Vec3f position);

    void move_position(math::Vec3f displacement);

    math::Vec3f get_position() const;


    void set_rotation(float rotation);

    void move_rotation(float angle);

    float get_rotation() const;


    math::Mat4f get_projection() const;

    math::Mat4f get_view() const;

    math::Mat4f get_view_projection() const;

private:
    math::Mat4f m_projection;
    math::Mat4f m_view;
    math::Mat4f m_view_projection;

    math::Vec3f m_position;
    float m_rotation;

    void compute_matrices();
};

}