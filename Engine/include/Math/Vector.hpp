#pragma once

#include <array>
#include <inttypes.h>
#include <cmath>

namespace math {

template<typename T, uint32_t N>
class Vector {
public:
    Vector();

    Vector(const std::array<T,N>& component);

    T Norm() const;

    T Norm2() const;

    void Normalize();

    std::array<T,N>& Data();

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
T Vector<T,N>::Norm() const {
    return sqrt(Norm2());
}

template<typename T, uint32_t N>
T Vector<T,N>::Norm2() const {
    T n(0);
    for (auto& com : m_component) {
        n += com;
    }
    return n;
}

template<typename T, uint32_t N>
void Vector<T,N>::Normalize() {
    T n(1.0/Norm());
    for (auto& com : m_component) {
        com *= n;
    }
}

template<typename T, uint32_t N>

std::array<T,N>& Vector<T,N>::Data() {
    return m_component;
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