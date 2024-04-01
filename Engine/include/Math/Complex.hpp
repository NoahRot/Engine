#pragma once

#include <iostream>
#include <cmath>

namespace math {

enum struct ComplexRepresentation {
    Cartesian,
    Polar
};

template<typename T>
class Complex {
public:
    Complex(T re_mag, T im_arg, ComplexRepresentation representation = ComplexRepresentation::Cartesian);

    T& real() { return m_re; }
    T& imag() { return m_im; }
    T real() const { return m_re; }
    T imag() const { return m_im; }
    T argu() const { return atan2f(m_im, m_re); }
    T magn() const { return sqrtf(m_re * m_re + m_im * m_im); }

    void normalize();

    Complex& operator+=(const Complex& z);
    Complex& operator-=(const Complex& z);
    Complex& operator*=(const Complex& z);
    Complex& operator*=(T a);
    Complex& operator-();

private:
    T m_re;
    T m_im;
};

// ========================================
// External operators 
// ========================================

template<typename T>
Complex<T> operator+(Complex<T> z1, const Complex<T>& z2);

template<typename T>
Complex<T> operator-(Complex<T> z1, const Complex<T>& z2);

template<typename T>
Complex<T> operator*(Complex<T> z1, const Complex<T>& z2);

template<typename T>
Complex<T> operator*(Complex<T> z, T a);

template<typename T>
Complex<T> operator*(T a, Complex<T> z);

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Complex<T>& z);

// ========================================
// Definitions 
// ========================================

template<typename T>
Complex<T>::Complex(T re_mag, T im_arg, ComplexRepresentation representation)
{
    switch (representation) {
        case ComplexRepresentation::Cartesian:
            m_re = re_mag;
            m_im = im_arg;
            break;

        case ComplexRepresentation::Polar:
            m_re = re_mag * cosf(im_arg);
            m_im = re_mag * sinf(im_arg);
            break;
    }
}

template<typename T>
void Complex<T>::normalize() {
    T m = magn();
    m_re /= m;
    m_im /= m;
}

template<typename T>
Complex<T>&  Complex<T>::operator+=(const Complex<T>& z) {
    m_re += z.m_re;
    m_im += z.m_im;
    return *this;
}

template<typename T>
Complex<T>& Complex<T>::operator-=(const Complex<T>& z) {
    m_re -= z.m_re;
    m_im -= z.m_im;
    return *this;
}

template<typename T>
Complex<T>& Complex<T>::operator*=(const Complex<T>& z) {
    T re = m_re*z.m_re - m_im*z.m_im;
    T im = m_re*z.m_im + m_im*z.m_re;
    m_re = re;
    m_im = im;
    return *this;
}

template<typename T>
Complex<T>& Complex<T>::operator*=(T a) {
    m_re *= a;
    m_im *= a;
    return *this;
}

template<typename T>
Complex<T>& Complex<T>::operator-(){
    m_re = -m_re;
    m_im = -m_im;
    return *this;
}

// ========================================
// External operators 
// ========================================

template<typename T>
Complex<T> operator+(Complex<T> z1, const Complex<T>& z2) {
    z1 += z2;
    return z1;
}

template<typename T>
Complex<T> operator-(Complex<T> z1, const Complex<T>& z2) {
    z1 -= z2;
    return z1;
}

template<typename T>
Complex<T> operator*(Complex<T> z1, const Complex<T>& z2) {
    z1 *= z2;
    return z1;
}

template<typename T>
Complex<T> operator*(Complex<T> z, T a) {
    z *= a;
    return z;
}

template<typename T>
Complex<T> operator*(T a, Complex<T> z) {
    z *= a;
    return z;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Complex<T>& z) {
    stream << z.real() << " + i" << z.imag();
    return stream;
}

}