#pragma once

#include "Math/Vector.hpp"
#include "Math/Matrix.hpp"
#include "Math/Function.hpp"

namespace math {

// Vector
typedef math::Vector<int, 2>    Vec2i;
typedef math::Vector<float, 2>  Vec2f;
typedef math::Vector<double, 2> Vec2d;

typedef math::Vector<int, 3>    Vec3i;
typedef math::Vector<float, 3>  Vec3f;
typedef math::Vector<double, 3> Vec3d;

typedef math::Vector<int, 4>    Vec4i;
typedef math::Vector<float, 4>  Vec4f;
typedef math::Vector<double, 4> Vec4d;

// Matrix
typedef math::Matrix<int, 2, 2>     Mat2i;
typedef math::Matrix<float, 2, 2>   Mat2f;
typedef math::Matrix<double, 2, 2>  Mat2d;

typedef math::Matrix<int, 3, 3>     Mat3i;
typedef math::Matrix<float, 3, 3>   Mat3f;
typedef math::Matrix<double, 3, 3>  Mat3d;

typedef math::Matrix<int, 4, 4>     Mat4i;
typedef math::Matrix<float, 4, 4>   Mat4f;
typedef math::Matrix<double, 4, 4>  Mat4d;
}