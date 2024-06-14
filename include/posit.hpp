#ifndef POSIT_HPP
#define POSIT_HPP

#include <iostream>
#include <string>

template <class T, int total_bits, int exponent_bits>
class Posit {
    struct Posit_Type {
        short sign;
        T k;
        T exponent;
        T fraction;
        int total_bits;
        int exponent_bits;
        bool isZero = false;
        bool isNaN = false;
    };

public:
    Posit_Type posit_number;

    Posit(T number);
    Posit(float number = 0);
    Posit(const Posit& other);
    Posit& operator=(const Posit& other);

    void update_by_posit_value(T number = 0);
    void update_by_float_value(float number = 0);
    float calculate_float_value() const;
    T calculate_posit_value();

    Posit& operator+=(const Posit& other);
    Posit& operator-=(const Posit& other);
    Posit& operator*=(const Posit& other);
    Posit& operator/=(const Posit& other);

    Posit operator+(const Posit& other) const;
    Posit operator-(const Posit& other) const;
    Posit operator*(const Posit& other) const;
    Posit operator/(const Posit& other) const;
};

#include "posit.tpp"

#endif // POSIT_HPP
