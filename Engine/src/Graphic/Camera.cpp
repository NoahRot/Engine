#include "Graphic/Camera.hpp"

namespace eng {

Camera2D::Camera2D(float left, float right, float bottom, float top, mat::Vec3f position, float rotation)
: m_projection(mat::orthographic3<float>(left, right, bottom, top, 1.0f, -1.0f)), m_position(position), m_rotation(rotation)
{
    compute_matrices();
}

void Camera2D::set_position(mat::Vec3f position) {
    m_position = position;
    compute_matrices();
}

void Camera2D::move_position(mat::Vec3f displacement) {
    m_position += displacement;
    compute_matrices();
}

mat::Vec3f Camera2D::get_position() const {
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

mat::Mat4f Camera2D::get_projection() const {
    return m_projection;
}

mat::Mat4f Camera2D::get_view() const {
    return m_view;
}

mat::Mat4f Camera2D::get_view_projection() const {
    return m_view_projection;
}

void Camera2D::compute_matrices() {
    m_view = mat::dot(mat::translate3<float>(-1.0f * m_position), mat::rotateZ(m_rotation));
    m_view_projection = mat::dot(m_projection, m_view);
}

}