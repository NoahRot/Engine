#pragma once

#include "Math/Vector.hpp"
#include "Math/Matrix.hpp"
#include "Math/Complex.hpp"

namespace math {

// ========================================
// Prototype 
// ========================================

/// @brief Compute the dot product between two vectors
/// @tparam T The type of the vectors
/// @tparam N The dimension of the vectors
/// @param v1 The first vector
/// @param v2 The second vector
/// @return The dot product between the two vectors
template<typename T, uint32_t N>
T dot(const Vector<T,N>& v1, const Vector<T,N>& v2);

/// @brief Compute the cross product between two vectors of dimension 3
/// @tparam T The type of the vectors
/// @param v1 The first vector
/// @param v2 The second vector
/// @return The cross product between the two vectors
template<typename T>
Vector<T,3> cross(const Vector<T,3>& v1, const Vector<T,3>& v2);

/// @brief Compute the cross product between two vectors of dimension 2
/// @tparam T The type of the vectors
/// @param v1 The first vector
/// @param v2 The second vector
/// @return The cross product between the two vectors
template<typename T>
T cross(const Vector<T,2>& v1, const Vector<T,2>& v2);

/// @brief Compute the angle between two vectors of dimension 3
/// @tparam T The type of vector
/// @param v1 The first vector
/// @param v2 The second vector
/// @return The angle between the two vectors
template<typename T>
T angle(const Vector<T,3>& v1, const Vector<T,3>& v2);

/// @brief Compute the angle between two vectors of dimension 2
/// @tparam T The type of vector
/// @param v1 The first vector
/// @param v2 The second vector
/// @return The angle between the two vectors
template<typename T>
T angle(const Vector<T,2>& v1, const Vector<T,2>& v2);

/// @brief Merge two vectors together
/// @tparam T The type of vector
/// @tparam N The dimension of the first vector
/// @tparam M The dimension of the second vector
/// @param v1 The first vector
/// @param v2 The second vector
/// @return A vector of dimension N+M, which is the two vectors merged
template<typename T, uint32_t N, uint32_t M>
Vector<T, N+M> merge(const Vector<T,N>& v1, const Vector<T,M>& v2);

/// @brief Merge a vectors with a scalar
/// @tparam T The type of vector
/// @tparam N The dimension of the vector
/// @param v1 The vector
/// @param a The scalar
/// @return A vector of dimension N+1, which is the vector merged with the scalar
template<typename T, uint32_t N>
Vector<T, N+1> merge(const Vector<T,N>& v1, T a);

/// @brief Merge a vectors with a scalar
/// @tparam T The type of vector
/// @tparam N The dimension of the vector
/// @param a The scalar
/// @param v1 The vector
/// @return A vector of dimension N+1, which is the vector merged with the scalar
template<typename T, uint32_t N>
Vector<T, N+1> merge(T a, const Vector<T,N>& v1);

/// @brief Transpose a square matrix
/// @tparam T The type of matrix
/// @tparam N The dimensions of the matrix
/// @param m The matrix
template<typename T, uint32_t N>
void transpose(Matrix<T,N,N>& m);

template<typename T, uint32_t L, uint32_t C>
Vector<T, L> operator*(const Matrix<T,L,C>& m, const Vector<T, C>& v);

template<typename T, uint32_t L, uint32_t C>
Vector<T, C> operator*(const Vector<T, L>& v, const Matrix<T,L,C>& m);

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

template<typename T>
T angle(const Vector<T,3>& v1, const Vector<T,3>& v2) {
    return atan2f(cross<float>(v1, v2).norm(), dot<float,3>(v1, v2));
}

template<typename T>
T angle(const Vector<T,2>& v1, const Vector<T,2>& v2) {
    return atan2f(cross<float>(v1, v2), dot<float,2>(v1, v2));
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

template<typename T, uint32_t N>
void transpose(Matrix<T,N,N>& m) {
    for (uint32_t i(1) ; i < N ; ++i) {
        for (uint32_t k(0) ; k <= i ; ++k) {
            std::swap(m.Get(i,k), m.Get(k,i));
        }
    }
}

template<typename T, uint32_t L, uint32_t C>
Vector<T, L> operator*(const Matrix<T,L,C>& m, const Vector<T, C>& v) {
    Vector<T,L> result;
    for (uint32_t i(0) ; i < L ; ++i) {
        for (uint32_t j(0) ; j < C ; ++j) {
            result[i] += m.Get(j,i)*v[j];
        }
    }
    return result;
}

template<typename T, uint32_t L, uint32_t C>
Vector<T, C> operator*(const Vector<T, L>& v, const Matrix<T,L,C>& m) {
    Vector<T,C> result;
    for (uint32_t i(0) ; i < C ; ++i) {
        for (uint32_t j(0) ; j < L ; ++j) {
            result[i] += v[j]*m.Get(i,j);
        }
    }
    return result;
}

}