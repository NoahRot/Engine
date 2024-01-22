#pragma once

#include "Math/Vector.hpp"

namespace math {

template<typename T, uint32_t N>
T dot(const Vector<T,N>& v1, const Vector<T,N>& v2);

template<typename T>
Vector<T,3> cross(const Vector<T,3>& v1, const Vector<T,3>& v2);

template<typename T>
T cross(const Vector<T,2>& v1, const Vector<T,2>& v2);

template<typename T, uint32_t N, uint32_t M>
Vector<T, N+M> merge(const Vector<T,N>& v1, const Vector<T,M>& v2);

template<typename T, uint32_t N>
Vector<T, N+1> merge(const Vector<T,N>& v1, T a);

template<typename T, uint32_t N>
Vector<T, N+1> merge(T a, const Vector<T,N>& v1);

// ========================================
// Definitions 
// ========================================

template<typename T, uint32_t N>
T dot(const Vector<T,N>& v1, const Vector<T,N>& v2) {
    T a(0);
    for (size_t i(0) ; i < N ; ++i) {
        a += v1[i]*v2[i];
    }
    return a;
}

template<typename T>
Vector<T,3> cross(const Vector<T,3>& v1, const Vector<T,3>& v2) {
    return Vector<T,3>({
        v1[1]*v2[2] - v1[2]*v2[1],
        -v1[0]*v2[2] + v1[2]*v2[0],
        v1[0]*v2[1] - v1[1]*v2[0]
    });
}

template<typename T>
T cross(const Vector<T,2>& v1, const Vector<T,2>& v2) {
    return v1[0]*v2[1] - v1[1]*v2[0];
}

template<typename T, uint32_t N, uint32_t M>
Vector<T, N+M> merge(const Vector<T,N>& v1, const Vector<T,M>& v2) {
    Vector<T, N+M> v;
    for (uint32_t i(0) ; i < N+M ; ++i) {
        v[i]= (i < N) ? v1[i] : v2[i-N];
    }
    return v;
}

template<typename T, uint32_t N>
Vector<T, N+1> merge(const Vector<T,N>& v1, T a) {
    Vector<T, N+1> v;
    for (uint32_t i(0) ; i < N ; ++i) {
        v[i] = v1[i];
    }
    v[N] = a;
    return v;
}

template<typename T, uint32_t N>
Vector<T, N+1> merge(T a, const Vector<T,N>& v1) {
    Vector<T, N+1> v;
    v[0] = a;
    for (uint32_t i(0) ; i < N ; ++i) {
        v[i+1] = v1[i];
    }
    return v;
}

}