#pragma once

#include "Math/Math.hpp"

#include "Core/Window.hpp"

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




class Camera3D {
public:
    Camera3D(float fov, float near, float far);

    void set_fov(float fov) { m_fov = fov; compute_projection(); }
    void set_near(float near) { m_near = near; compute_projection(); }
    void set_far(float far) { m_far = far; compute_projection(); }

    float get_fov() { return m_fov; }
    float get_near() { return m_near; }
    float get_far() { return m_far; }

    math::Vec4f get_position() const { return m_position; }
    math::Vec4f get_orientation() const { return m_orientation; }

    void set_position(math::Vec3f position) { m_position = math::Vec4f({position[0], position[1], position[2], 1.0f}); compute_view(); }
    void set_orientation(math::Vec3f orientation) { m_orientation = math::Vec4f({orientation[0], orientation[1], orientation[2], 1.0f}); compute_view(); }

    void transform_position(const math::Mat4f& transform) { m_position = transform * m_position; compute_view(); }
    void transform_orientation(const math::Mat4f& transform) { m_orientation = transform * m_orientation; compute_view(); }

    void look_at(math::Vec3f at);

    math::Mat4f get_projection() const { return m_projection; }
    math::Mat4f get_view() const { return m_view; }
    math::Mat4f get_view_projection() const { return m_view_projection; }

private:
    math::Mat4f m_projection;
    math::Mat4f m_view;
    math::Mat4f m_view_projection;

    math::Vec4f m_position;
    math::Vec4f m_orientation;

    float m_fov;
    float m_near;
    float m_far;

    void compute_projection();
    void compute_view();
};

}