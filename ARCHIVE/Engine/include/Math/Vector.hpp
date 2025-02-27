#pragma once

#include <array>
#include <inttypes.h>
#include <cmath>
#include <iostream>

namespace math {

/// @brief Mathematical vector of type T and dimension N
/// @tparam T The type of vector
/// @tparam N The dimension of the vector
template<typename T, uint32_t N>
class Vector {
public:
    /// @brief Constructor. The vector is fill with 0.
    Vector();

    /// @brief Constructor
    /// @param component The components of the vector
    Vector(const std::array<T,N>& component);

    /// @brief Compute the norm of the vector
    /// @return The norm of the vector
    T norm() const;

    /// @brief Compute the square of the norm
    /// @return The square of the norm
    T norm2() const;

    /// @brief Normalize the vector
    /// @warning Doesn't check if the norm is null
    void normalize();

    /// @brief Return a reference to the component of the vector
    /// @return The components
    std::array<T,N>& data();

    /// @brief Return a pointer to the first element
    /// @return A pointer to the first element
    T* front_ptr() const;

    Vector& operator+=(const Vector& v);

    Vector& operator-=(const Vector& v);

    Vector& operator*=(T a);

    Vector& operator/=(T a);

    Vector& operator-();

    T& operator[](uint32_t index);

    T operator[](uint32_t index) const;

private:
    std::array<T, N> m_component;
};

// ========================================
// External operators 
// ========================================

template<typename T, uint32_t N>
Vector<T,N> operator+(Vector<T,N> v1, const Vector<T,N>& v2);

template<typename T, uint32_t N>
Vector<T,N> operator-(Vector<T,N> v1, const Vector<T,N>& v2);

template<typename T, uint32_t N>
Vector<T,N> operator*(Vector<T,N> v1, T a);

template<typename T, uint32_t N>
Vector<T,N> operator*(T a, Vector<T,N> v1);

template<typename T, uint32_t N>
T operator*(const Vector<T,N>& v1, const Vector<T,N>& v2);

template<typename T>
Vector<T,3> operator^(const Vector<T,3>& v1, const Vector<T,3>& v2);

template<typename T, uint32_t N>
std::ostream& operator<<(std::ostream& stream, const Vector<T,N>& v1);

// ========================================
// Definitions 
// ========================================

template<typename T, uint32_t N>
Vector<T,N>::Vector() {
    m_component.fill((T)0);
}

template<typename T, uint32_t N>
Vector<T,N>::Vector(const std::array<T,N>& component) 
: m_component(component)
{}

template<typename T, uint32_t N>
T Vector<T,N>::norm() const {
    return sqrt(norm2());
}

template<typename T, uint32_t N>
T Vector<T,N>::norm2() const {
    T n(0);
    for (auto& com : m_component) {
        n += com;
    }
    return n;
}

template<typename T, uint32_t N>
void Vector<T,N>::normalize() {
    T n(1.0/norm());
    for (auto& com : m_component) {
        com *= n;
    }
}

template<typename T, uint32_t N>
std::array<T,N>& Vector<T,N>::data() {
    return m_component;
}

template<typename T, uint32_t N>
T* Vector<T,N>::front_ptr() const {
    return (T*)(&m_component[0]);
}

template<typename T, uint32_t N>
Vector<T,N>& Vector<T,N>::operator+=(const Vector& v) {
    for (uint32_t i(0) ; i < N ; ++i) {
        m_component[i] += v.m_component[i];
    }
    return *this;
}

template<typename T, uint32_t N>
Vector<T,N>& Vector<T,N>::operator-=(const Vector& v) {
    for (uint32_t i(0) ; i < N ; ++i) {
        m_component[i] -= v.m_component[i];
    }
    return *this;
}

template<typename T, uint32_t N>
Vector<T,N>& Vector<T,N>::operator*=(T a) {
    for (uint32_t i(0) ; i < N ; ++i) {
        m_component[i] *= a;
    }
    return *this;
}

template<typename T, uint32_t N>
Vector<T,N>& Vector<T,N>::operator/=(T a) {
    T b(1.0/a);
    for (uint32_t i(0) ; i < N ; ++i) {
        m_component[i] *= b;
    }
    return *this;
}

template<typename T, uint32_t N>

Vector<T,N>& Vector<T,N>::operator-() {
    for (auto& com : m_component) {
        com = -com;
    }
    return *this;
}

template<typename T, uint32_t N>
T& Vector<T,N>::operator[](uint32_t index) {
    return m_component[index];
}

template<typename T, uint32_t N>
T Vector<T,N>::operator[](uint32_t index) const {
    return m_component[index];
}

// ========================================
// External operators 
// ========================================

template<typename T, uint32_t N>
Vector<T,N> operator+(Vector<T,N> v1, const Vector<T,N>& v2) {
    return v1+=v2;
}

template<typename T, uint32_t N>
Vector<T,N> operator-(Vector<T,N> v1, const Vector<T,N>& v2) {
    return v1-=v2;
}

template<typename T, uint32_t N>
Vector<T,N> operator*(Vector<T,N> v1, T a) {
    return v1*=a;
}

template<typename T, uint32_t N>
Vector<T,N> operator*(T a, Vector<T,N> v1) {
    return v1*=a;
}

template<typename T, uint32_t N>
T operator*(const Vector<T,N>& v1, const Vector<T,N>& v2) {
    T result(0);
    for (uint32_t i(0) ; i < N ; ++i) {
        result += v1[i]*v2[i];
    }
    return result;
}

template<typename T>
Vector<T,3> operator^(const Vector<T,3>& v1, const Vector<T,3>& v2) {
    Vector<T,3> result;
    result[0] = v1[1]*v2[2] - v1[2]*v2[1];
    result[1] = -v1[0]*v2[2] + v1[2]*v2[0];
    result[2] = v1[0]*v2[1] - v1[1]*v2[0];
    return result;
}

template<typename T, uint32_t N>
std::ostream& operator<<(std::ostream& stream, const Vector<T,N>& v1) {
    stream << "Vec[" << N << "] = (";
    for (uint32_t i(0) ; i < N ; ++i) {
        stream << v1[i];
        if (i != N-1) {
            stream << ", ";
        }
    }
    stream << ")";
    return stream;
}

}