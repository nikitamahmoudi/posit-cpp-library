#ifndef POSIT_TPP
#define POSIT_TPP

#include "posit.hpp"
#include <cmath>
#include <bitset>

template <class T, int total_bits, int exponent_bits>
Posit<T, total_bits, exponent_bits>::Posit(T number) {
    posit_number.total_bits = total_bits;
    posit_number.exponent_bits = exponent_bits;
    update_by_posit_value(number);
}

template <class T, int total_bits, int exponent_bits>
Posit<T, total_bits, exponent_bits>::Posit(float number) {
    posit_number.total_bits = total_bits;
    posit_number.exponent_bits = exponent_bits;
    update_by_float_value(number);
}

template <class T, int total_bits, int exponent_bits>
Posit<T, total_bits, exponent_bits>::Posit(const Posit& other) {
    posit_number = other.posit_number;
}

template <class T, int total_bits, int exponent_bits>
Posit<T, total_bits, exponent_bits>& Posit<T, total_bits, exponent_bits>::operator=(const Posit& other) {
    if (this != &other) {
        posit_number = other.posit_number;
    }
    return *this;
}

template <class T, int total_bits, int exponent_bits>
void Posit<T, total_bits, exponent_bits>::update_by_posit_value(T number) {
    posit_number.isZero = false;
    posit_number.isNaN = false;

    if (number == 0) {
        posit_number.sign = 0;
        posit_number.k = 0;
        posit_number.exponent = 0;
        posit_number.fraction = 0;
        posit_number.isZero = true;
        return;
    }

    if (isnan(static_cast<float>(number))) {
        posit_number.sign = 1;
        posit_number.k = 0;
        posit_number.exponent = 0;
        posit_number.fraction = 0;
        posit_number.isNaN = true;
        return;
    }

    posit_number.sign = (number & (1 << (total_bits - 1))) >> (total_bits - 1);
    if (posit_number.sign == 1) number *= -1;

    char type = (number & (1 << (total_bits - 2))) >> (total_bits - 2);
    char current_bit;
    char type_count = 1;
    posit_number.k = 0;

    for (int i = total_bits - 2; i >= 1; i--) {
        current_bit = (number & (1 << (i - 1))) >> (i - 1);
        if (type != current_bit) break;
        type_count++;
    }

    posit_number.k = (type == 0) ? -type_count : type_count - 1;

    posit_number.exponent = 0;
    for (int i = total_bits - type_count - 2; i >= total_bits - type_count - 2 - exponent_bits + 1; i--)
        posit_number.exponent += (number & (1 << (i - 1))) >> (total_bits - type_count - 2 - exponent_bits);

    posit_number.fraction = 0;
    for (int i = total_bits - type_count - 2 - exponent_bits; i >= 1; i--)
        posit_number.fraction += (number & (1 << (i - 1)));

    return;
}

template <class T, int total_bits, int exponent_bits>
void Posit<T, total_bits, exponent_bits>::update_by_float_value(float number) {
    posit_number.isZero = false;
    posit_number.isNaN = false;
    if (number == 0) {
        posit_number.sign = 0;
        posit_number.k = 0;
        posit_number.exponent = 0;
        posit_number.fraction = 0;
        posit_number.isZero = true;
        return;
    }

    int scale = pow(2, pow(2, exponent_bits));
    posit_number.sign = (number < 0) ? 1 : 0;
    if (number < 0) number *= -1;

    posit_number.k = 0;
    while (number > scale) {
        posit_number.k++;
        number /= scale;
    }
    while (number < 1) {
        posit_number.k--;
        number *= scale;
    }

    posit_number.exponent = 0;
    while (number >= 2) {
        posit_number.exponent++;
        number /= 2;
    }
    posit_number.fraction = (number - 1) * scale;
}

template <class T, int total_bits, int exponent_bits>
float Posit<T, total_bits, exponent_bits>::calculate_float_value() const {
    if (posit_number.isZero)
        return 0.0f;
    if (posit_number.isNaN)
        return NAN;

    int scale = pow(2, pow(2, exponent_bits));
    float decoded_number = pow(scale, posit_number.k) * pow(2, posit_number.exponent) * (1.0f + static_cast<float>(posit_number.fraction) / scale);
    if (posit_number.sign == 1) decoded_number *= -1;

    return decoded_number;
}

template <class T, int total_bits, int exponent_bits>
T Posit<T, total_bits, exponent_bits>::calculate_posit_value() {
    std::string converted_k;
    if (posit_number.k > 0) {
        for (int i = 0; i < posit_number.k + 1; i++) converted_k += "1";
    }
    else {
        for (int i = 0; i < -posit_number.k; i++) converted_k += "0";
    }
    converted_k += (posit_number.k > 0) ? "0" : "1";

    T calculated_posit = stoi(converted_k, nullptr, 2) * pow(2, (total_bits - 1 - converted_k.length())) +
        posit_number.exponent * pow(2, (total_bits - 1 - converted_k.length() - exponent_bits)) +
        posit_number.fraction;

    if (posit_number.sign == 1) calculated_posit *= -1;

    return calculated_posit;
}

template <class T, int total_bits, int exponent_bits>
Posit<T, total_bits, exponent_bits>& Posit<T, total_bits, exponent_bits>::operator+=(const Posit& other) {
    update_by_float_value(this->calculate_float_value() + other.calculate_float_value());
    return *this;
}

template <class T, int total_bits, int exponent_bits>
Posit<T, total_bits, exponent_bits>& Posit<T, total_bits, exponent_bits>::operator-=(const Posit& other) {
    update_by_float_value(this->calculate_float_value() - other.calculate_float_value());
    return *this;
}

template <class T, int total_bits, int exponent_bits>
Posit<T, total_bits, exponent_bits>& Posit<T, total_bits, exponent_bits>::operator*=(const Posit& other) {
    update_by_float_value(this->calculate_float_value() * other.calculate_float_value());
    return *this;
}

template <class T, int total_bits, int exponent_bits>
Posit<T, total_bits, exponent_bits>& Posit<T, total_bits, exponent_bits>::operator/=(const Posit& other) {
    update_by_float_value(this->calculate_float_value() / other.calculate_float_value());
    return *this;
}

template <class T, int total_bits, int exponent_bits>
Posit<T, total_bits, exponent_bits> Posit<T, total_bits, exponent_bits>::operator+(const Posit& other) const {
    Posit result = *this;
    result += other;
    return result;
}

template <class T, int total_bits, int exponent_bits>
Posit<T, total_bits, exponent_bits> Posit<T, total_bits, exponent_bits>::operator-(const Posit& other) const {
    Posit result = *this;
    result -= other;
    return result;
}

template <class T, int total_bits, int exponent_bits>
Posit<T, total_bits, exponent_bits> Posit<T, total_bits, exponent_bits>::operator*(const Posit& other) const {
    Posit result = *this;
    result *= other;
    return result;
}

template <class T, int total_bits, int exponent_bits>
Posit<T, total_bits, exponent_bits> Posit<T, total_bits, exponent_bits>::operator/(const Posit& other) const {
    Posit result = *this;
    result /= other;
    return result;
}

#endif // POSIT_TPP
