#pragma once

#include "Math/Matrix.hpp"
#include <cmath>

namespace math {

// ========================================
// Prototype 
// ========================================

// 2D Transformations

template<typename T>
Matrix<T, 3, 3> translate2(const Vector<T,2>& v);

template<typename T>
Matrix<T, 3, 3> rotate2(T angle);

template<typename T>
Matrix<T, 3, 3> scale2(T sx, T sy);

template<typename T>
Matrix<T, 3, 3> scale2(T s);

template<typename T>
Matrix<T, 3, 3> orthographic2(T left, T right, T bottom, T top);

// 3D Transformations

template<typename T>
Matrix<T, 4, 4> translate3(const Vector<T,3>& vect);

template<typename T>
Matrix<T, 4, 4> rotateX(T angle);

template<typename T>
Matrix<T, 4, 4> rotateY(T angle);

template<typename T>
Matrix<T, 4, 4> rotateZ(T angle);

template<typename T>
Matrix<T, 4, 4> scale3(T sx, T sy, T sz);

template<typename T>
Matrix<T, 4, 4> scale3(T s);

template<typename T>
Matrix<T, 4, 4> orthographic3(T left, T right, T bottom, T top, T near, T far);

template<typename T>
Matrix<T, 4, 4> perspective(T aspectRatio, T fov, T n, T f);

template<typename T>
Matrix<T, 4, 4> look_at(const Vector<T, 3>& position, const Vector<T, 3>& target);

// ========================================
// Definitions 
// ========================================

// 2D Transformations

template<typename T>
Matrix<T, 3, 3> translate2(const Vector<T,2>& v) {
    Matrix<T,3,3> m;
    m.get(2,0) = v[0];
    m.get(2,1) = v[1];
    return m;
}

template<typename T>
Matrix<T, 3, 3> rotate2(T angle) {
    T c = cosf(angle);
    T s = sinf(angle);
    Matrix<T,3,3> m({
        c,      s,      (T)0,
        -s,     c,      (T)0,
        (T)0,   (T)0,   (T)1
    });
    return m;
}

template<typename T>
Matrix<T, 3, 3> scale2(T sx, T sy) {
    Matrix<T,3,3> m({
        sx,     (T)0,   (T)0,
        (T)0,   sy,     (T)0,
        (T)0,   (T)0,   (T)1
    });
    return m;
}

template<typename T>
Matrix<T, 3, 3> scale2(T s) {
    Matrix<T,3,3> m({
        s,      (T)0,   (T)0,
        (T)0,   s,      (T)0,
        (T)0,   (T)0,   (T)1
    });
    return m;
}

template<typename T>
Matrix<T,3,3> orthographic2(T left, T right, T bottom, T top) {
    Matrix<T,3,3> m({
        (T)2/(right-left), (T)0, (T)0,
        (T)0, (T)2/(top-bottom), (T)0,
        -(right+left)/(right-left), -(top+bottom)/(top-bottom), (T)1

    });
    return m;
}

// 3D Transformations

template<typename T>
Matrix<T, 4, 4> translate3(const Vector<T,3>& vect) {
    Matrix<T, 4, 4> m;
    m.get(3,0) = vect[0];
    m.get(3,1) = vect[1];
    m.get(3,2) = vect[2];
    return m;
}

template<typename T>
Matrix<T, 4, 4> rotateX(T angle) {
    T s = sinf(angle);
    T c = cosf(angle);
    Matrix<T,4,4> m({
        (T)1,   (T)0, (T)0,   (T)0,
        (T)0,   c,    -s,     (T)0,
        (T)0,   s,    c,      (T)0,
        (T)0,   (T)0, (T)0,   (T)1
    });
    return m;
}

template<typename T>
Matrix<T, 4, 4> rotateY(T angle) {
    T s = sinf(angle);
    T c = cosf(angle);
    Matrix<T,4,4> m({
        c,      (T)0,   s,      (T)0,
        (T)0,   (T)1,   (T)0,   (T)0,
        -s,     (T)0,   c,      (T)0,
        (T)0,   (T)0,   (T)0,   (T)1
    });
    return m;
}

template<typename T>
Matrix<T, 4, 4> rotateZ(T angle) {
    T s = sinf(angle);
    T c = cosf(angle);
    Matrix<T,4,4> mat({
        c,      -s,     (T)0,   (T)0,
        s,      c,      (T)0,   (T)0,
        (T)0,   (T)0,   (T)1,   (T)0,
        (T)0,   (T)0,   (T)0,   (T)1
    });
    return mat;
}

template<typename T>
Matrix<T, 4, 4> scale3(T sx, T sy, T sz) {
    Matrix<T,4,4> mat({
        sx,     (T)0,   (T)0,   (T)0,
        (T)0,   sy,     (T)0,   (T)0,
        (T)0,   (T)0,   sz,     (T)0,
        (T)0,   (T)0,   (T)0,   (T)1
    });
    return mat;
}

template<typename T>
Matrix<T, 4, 4> scale3(T s) {
    Matrix<T,4,4> mat({
        s,      (T)0,   (T)0,   (T)0,
        (T)0,   s,      (T)0,   (T)0,
        (T)0,   (T)0,   s,      (T)0,
        (T)0,   (T)0,   (T)0,   (T)1
    });
    return mat;
}


template<typename T>
Matrix<T,4,4> orthographic3(T left, T right, T bottom, T top, T near, T far) {
    Matrix<T,4,4> mat({
        (T)2/(right-left), (T)0, (T)0, (T)0,
        (T)0, (T)2/(top-bottom), (T)0, (T)0,
        (T)0, (T)0, -(T)2/(far-near), (T)0,
        -(right+left)/(right-left), -(top+bottom)/(top-bottom), -(far+near)/(far-near), (T)1

    });
    return mat;
}

template<typename T>
Matrix<T,4,4> perspective(T aspectRatio, T fov, T n, T f) {
    T t = tanf(0.5f*fov)*n;
    T b = -t;
    T r = t*aspectRatio;
    T l = -r;
    Matrix<T,4,4> mat({
        2*n/(r-l), (T)0, (T)0, (T)0,
        (T)0, 2*n/(t-b), (T)0, (T)0,
        (r+l)/(r-l), (t+b)/(t-b), -(f+n)/(f-n), (T)-1,
        (T)0, (T)0, -2*f*n/(f-n), (T)0
    });
    return mat;
}

template<typename T>
Matrix<T, 4, 4> look_at(const Vector<T, 3>& position, const Vector<T, 3>& target) {
    Vector<T, 3> up({0.0f, 1.0f, 0.0f});
    Vector<T, 3> direction(position - target);
    direction.normalize();
    Vector<T, 3> right(cross(up, direction));
    Vector<T, 3> camera_up(cross(direction, right));

    return Matrix<T, 4, 4>({
        right[0],   camera_up[0],   direction[0],   (T)0,
        right[1],   camera_up[1],   direction[1],   (T)0,
        right[2],   camera_up[2],   direction[2],   (T)0,
        (T)0,       (T)0,           (T)0,           (T)1
    }) * translate3<T>(position);
}

}