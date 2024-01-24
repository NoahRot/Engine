#pragma once

#include <cmath>
#include <inttypes.h>
#include <array>
#include <ostream>

#include "Vector.hpp"

namespace math {

/*
Matrix LxC :
1,1  1,2  1,3  ...  1,C
2,1  2,2  2,3  ...  2,C
3,1  3,2  3,3  ...  3,C
4,1  4,2  4,3  ...  4,C
...  ...  ...  ...  ...
L,1  L,2  L,3  ...  L,C


Store as :
    1,1  2,1  3,1  4,1  5,1  ...
*/

/// @brief Matrix class
/// @tparam T The type of matrix
/// @tparam L Number of lines
/// @tparam C Number of column
template<typename T, uint32_t L, uint32_t C>
class Matrix {
public:
    Matrix();

    Matrix(const std::array<T, C+L>& component);

    Matrix(const std::array<Vector<T,L>, C>& component);

    T& Get(uint32_t column, uint32_t line);

    T Get(uint32_t column, uint32_t line) const;

    Vector<T,L>& Get(uint32_t column);

    std::array<T, C+L>& Data();

    std::array<Vector<T,L>, C>& DataVectorial();

    Matrix& operator+=(const Matrix<T,C,L>& m);

    Matrix& operator-=(const Matrix<T,C,L>& m);

    Matrix& operator*=(T a);

    Matrix& operator-();

    Vector<T,L>& operator[](uint32_t index);

    Vector<T,L> operator[](uint32_t index) const;

private:
    std::array<T, C+L> m_component;
};

// ========================================
// External operators 
// ========================================

template<typename T, uint32_t L, uint32_t C>
Matrix<T,L,C> operator+(Matrix<T,L,C> m1, const Matrix<T,L,C>& m2);

template<typename T, uint32_t L, uint32_t C>
Matrix<T,L,C> operator-(Matrix<T,L,C>&m1, const Matrix<T,L,C>& m2);

template<typename T, uint32_t L, uint32_t C>
Matrix<T,L,C> operator*(Matrix<T,L,C> m1, T a);

template<typename T, uint32_t L, uint32_t C>
Matrix<T,L,C> operator*(T a, Matrix<T,L,C> m1);

template<typename T, uint32_t M, uint32_t N, uint32_t Q>
Matrix<T,M,Q> operator*(const Matrix<T,M,N>& m1, const Matrix<T,N,Q>& m2);

template<typename T, uint32_t L, uint32_t C>
std::ostream& operator<<(std::ostream& stream, const Matrix<T,L,C>& m1);

// ========================================
// Definitions 
// ========================================

template<typename T, uint32_t L, uint32_t C>
Matrix<T,L,C>::Matrix() {
    if (L==C) {
        for (uint32_t i(0) ; i < C ; ++i) {
            for (uint32_t j(0) ; j < L ; ++j) {
                if (i == j) {
                    m_component[i*L + j] = (T)1;
                }else{
                    m_component[i*L + j] = (T)0;
                }
            }
        }
    }else{
        m_component.fill((T)0);
    }
}

template<typename T, uint32_t L, uint32_t C>
Matrix<T,L,C>::Matrix(const std::array<T, C+L>& component) 
: m_component(component)
{}

template<typename T, uint32_t L, uint32_t C>
Matrix<T,L,C>::Matrix(const std::array<Vector<T,L>, C>& component) {
    for (uint32_t i(0) ; i < C ; ++i) {
        for (uint32_t j(0) ; j < L ; ++j) {
            m_component[i*L + j] = component[i][j];
        }
    }
}

template<typename T, uint32_t L, uint32_t C>
T& Matrix<T,L,C>::Get(uint32_t column, uint32_t line) {
    return m_component[column*L + line];
}

template<typename T, uint32_t L, uint32_t C>
T Matrix<T,L,C>::Get(uint32_t column, uint32_t line) const  {
    return m_component[column*L + line];
}

template<typename T, uint32_t L, uint32_t C>
Vector<T,L>& Matrix<T,L,C>::Get(uint32_t column) {
    return (Vector<T,L>&)(*static_cast<Vector<T,L>*>(&m_component[column*L]));
}

template<typename T, uint32_t L, uint32_t C>
std::array<T, C+L>& Matrix<T,L,C>::Data() {
    return m_component;
}

template<typename T, uint32_t L, uint32_t C>
std::array<Vector<T,L>, C>& Matrix<T,L,C>::DataVectorial() {
    return (std::array<Vector<T,L>, C>&)(*static_cast<std::array<Vector<T,L>, C>*>(&m_component[0]));
}

template<typename T, uint32_t L, uint32_t C>
Matrix<T,L,C>& Matrix<T,L,C>::operator+=(const Matrix<T,C,L>& m) {
    for(uint32_t i(0) ; i < C*L ; ++i) {
        m_component[i] += m.m_component[i];
    }
}

template<typename T, uint32_t L, uint32_t C>
Matrix<T,L,C>& Matrix<T,L,C>::operator-=(const Matrix<T,C,L>& m) {
    for(uint32_t i(0) ; i < C*L ; ++i) {
        m_component[i] -= m.m_component[i];
    }
}

template<typename T, uint32_t L, uint32_t C>
Matrix<T,L,C>& Matrix<T,L,C>::operator*=(T a) {
    for(uint32_t i(0) ; i < C*L ; ++i) {
        m_component[i] *= a;
    }
}

template<typename T, uint32_t L, uint32_t C>
Matrix<T,L,C>& Matrix<T,L,C>::operator-() {
    for(uint32_t i(0) ; i < C*L ; ++i) {
        m_component[i] = -m_component[i];
    }
}

template<typename T, uint32_t L, uint32_t C>
Vector<T,L>& Matrix<T,L,C>::operator[](uint32_t index) {
    return (Vector<T,L>&)(*static_cast<Vector<T,L>*>(&m_component[index]));
}

template<typename T, uint32_t L, uint32_t C>
Vector<T,L> Matrix<T,L,C>::operator[](uint32_t index) const {
    return (Vector<T,L>)(*static_cast<Vector<T,L>*>(&m_component[index]));
}

// ========================================
// External operators 
// ========================================

template<typename T, uint32_t L, uint32_t C>
Matrix<T,L,C> operator+(Matrix<T,L,C> m1, const Matrix<T,L,C>& m2) {
    return m1 += m2;
}

template<typename T, uint32_t L, uint32_t C>
Matrix<T,L,C> operator-(Matrix<T,L,C>&m1, const Matrix<T,L,C>& m2) {
    return m1 -= m2;
}

template<typename T, uint32_t L, uint32_t C>
Matrix<T,L,C> operator*(Matrix<T,L,C> m1, T a) {
    return m1 *= a;
}

template<typename T, uint32_t L, uint32_t C>
Matrix<T,L,C> operator*(T a, Matrix<T,L,C> m1) {
    return m1 *= a;
}

template<typename T, uint32_t M, uint32_t N, uint32_t Q>
Matrix<T,M,Q> operator*(const Matrix<T,M,N>& m1, const Matrix<T,N,Q>& m2) {
    Matrix<T,M,Q> m;
    for (uint32_t i(0) ; i < M ; ++i) {
        for (uint32_t j(0) ; j < Q ; ++j) {
            T value(0);
            for(uint32_t k(0) ; k < N ; ++k) {
                value += m1.Get(i,k)*m2.Get(k,j);
            }
            m.Get(i,j) = value;
        }
    }
    return m;
}

template<typename T, uint32_t L, uint32_t C>
std::ostream& operator<<(std::ostream& stream, const Matrix<T,L,C>& m1) {
    stream << "Mat[" << L << "," << C << "]\n";
    for (uint32_t i(0) ; i < L ; ++i) {
        for (uint32_t j(0) ; j < C ; ++j) {
            stream << m1.Get(j,i);
            if (j != C-1) {
                stream << ", ";
            }
        }
        stream << "\n";
    }
    return stream;
}

}