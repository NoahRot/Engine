#include "Graphic/Camera.hpp"

namespace eng {

Camera2D::Camera2D(float left, float right, float bottom, float top, math::Vec3f position, float rotation)
: m_projection(math::orthographic3<float>(left, right, bottom, top, 1.0f, -1.0f)), m_position(position), m_rotation(rotation)
{
    compute_matrices();
}

void Camera2D::set_position(math::Vec3f position) {
    m_position = position;
    compute_matrices();
}

void Camera2D::move_position(math::Vec3f displacement) {
    m_position += displacement;
    compute_matrices();
}

math::Vec3f Camera2D::get_position() const {
    return m_position;
}

void Camera2D::set_rotation(float rotation) {
    m_rotation = rotation;
    compute_matrices();
}

void Camera2D::move_rotation(float angle) {
    m_rotation += angle;
    compute_matrices();
}

float Camera2D::get_rotation() const {
    return m_rotation;
}

math::Mat4f Camera2D::get_projection() const {
    return m_projection;
}

math::Mat4f Camera2D::get_view() const {
    return m_view;
}

math::Mat4f Camera2D::get_view_projection() const {
    return m_view_projection;
}

void Camera2D::compute_matrices() {
    m_view = math::translate3<float>(-1.0f * m_position) * math::rotateZ(m_rotation);
    m_view_projection = m_projection * m_view;
}


}