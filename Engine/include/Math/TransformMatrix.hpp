#pragma once

#include "Math/Matrix.hpp"
#include <cmath>

namespace math {

// ========================================
// Prototype 
// ========================================

// 2D Transformations

template<typename T>
Matrix<T, 3, 3> Translate2(const Vector<T,2>& v);

template<typename T>
Matrix<T, 3, 3> Rotate2(T angle);

template<typename T>
Matrix<T, 3, 3> Scale2(T sx, T sy);

template<typename T>
Matrix<T, 3, 3> Scale2(T s);

template<typename T>
Matrix<T, 3, 3> Orthographic2(T left, T right, T bottom, T top);

// 3D Transformations

template<typename T>
Matrix<T, 4, 4> Translate3(const Vector<T,3>& vect);

template<typename T>
Matrix<T, 4, 4> RotateX(T angle);

template<typename T>
Matrix<T, 4, 4> RotateY(T angle);

template<typename T>
Matrix<T, 4, 4> RotateZ(T angle);

template<typename T>
Matrix<T, 4, 4> Scale3(T sx, T sy, T sz);

template<typename T>
Matrix<T, 4, 4> Scale3(T s);

template<typename T>
Matrix<T,4,4> Orthographic3(T left, T right, T bottom, T top, T near, T far);

template<typename T>
Matrix<T,4,4> Perspective(T aspectRatio, T fov, T n, T f);

// ========================================
// Definitions 
// ========================================

// 2D Transformations

template<typename T>
Matrix<T, 3, 3> Translate2(const Vector<T,2>& v) {
    Matrix<T,3,3> m;
    m.Get(2,0) = v[0];
    m.Get(2,1) = v[1];
    return m;
}

template<typename T>
Matrix<T, 3, 3> Rotate2(T angle) {
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
Matrix<T, 3, 3> Scale2(T sx, T sy) {
    Matrix<T,3,3> m({
        sx,     (T)0,   (T)0,
        (T)0,   sy,     (T)0,
        (T)0,   (T)0,   (T)1
    });
    return m;
}

template<typename T>
Matrix<T, 3, 3> Scale2(T s) {
    Matrix<T,3,3> m({
        s,      (T)0,   (T)0,
        (T)0,   s,      (T)0,
        (T)0,   (T)0,   (T)1
    });
    return m;
}

template<typename T>
Matrix<T,3,3> Orthographic2(T left, T right, T bottom, T top) {
    Matrix<T,3,3> m({
        (T)2/(right-left), (T)0, (T)0,
        (T)0, (T)2/(top-bottom), (T)0,
        -(right+left)/(right-left), -(top+bottom)/(top-bottom), (T)1

    });
    return m;
}

// 3D Transformations

template<typename T>
Matrix<T, 4, 4> Translate3(const Vector<T,3>& vect) {
    Matrix<T, 4, 4> m;
    m.Get(3,0) = vect[0];
    m.Get(3,1) = vect[1];
    m.Get(3,2) = vect[2];
    return m;
}

template<typename T>
Matrix<T, 4, 4> RotateX(T angle) {
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
Matrix<T, 4, 4> RotateY(T angle) {
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
Matrix<T, 4, 4> RotateZ(T angle) {
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
Matrix<T, 4, 4> Scale3(T sx, T sy, T sz) {
    Matrix<T,4,4> mat({
        sx,     (T)0,   (T)0,   (T)0,
        (T)0,   sy,     (T)0,   (T)0,
        (T)0,   (T)0,   sz,     (T)0,
        (T)0,   (T)0,   (T)0,   (T)1
    });
    return mat;
}

template<typename T>
Matrix<T, 4, 4> Scale3(T s) {
    Matrix<T,4,4> mat({
        s,      (T)0,   (T)0,   (T)0,
        (T)0,   s,      (T)0,   (T)0,
        (T)0,   (T)0,   s,      (T)0,
        (T)0,   (T)0,   (T)0,   (T)1
    });
    return mat;
}


template<typename T>
Matrix<T,4,4> Orthographic3(T left, T right, T bottom, T top, T near, T far) {
    Matrix<T,4,4> mat({
        (T)2/(right-left), (T)0, (T)0, (T)0,
        (T)0, (T)2/(top-bottom), (T)0, (T)0,
        (T)0, (T)0, -(T)2/(far-near), (T)0,
        -(right+left)/(right-left), -(top+bottom)/(top-bottom), -(far+near)/(far-near), (T)1

    });
    return mat;
}

template<typename T>
Matrix<T,4,4> Perspective(T aspectRatio, T fov, T n, T f) {
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

}