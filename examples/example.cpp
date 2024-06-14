#include <iostream>
#include "posit.hpp"

int main() {
    // Create Posit objects from posit bits
    signed short number = 0b0000110111011101;
    Posit<short, 16, 3> posit1(number);

    // Create Posit objects from floating-point numbers
    float floatNumber = 3.14;
    Posit<short, 16, 3> posit2(floatNumber);

    // Display the float value of the Posit objects
    std::cout << "Float value of posit1: " << posit1.calculate_float_value() << std::endl;
    std::cout << "Float value of posit2: " << posit2.calculate_float_value() << std::endl;

    // Perform arithmetic operations
    Posit<short, 16, 3> positAdd = posit1 + posit2;
    Posit<short, 16, 3> positSub = posit1 - posit2;
    Posit<short, 16, 3> positMul = posit1 * posit2;
    Posit<short, 16, 3> positDiv = posit1 / posit2;

    // Display the results of arithmetic operations
    std::cout << "Result of addition: " << positAdd.calculate_float_value() << std::endl;
    std::cout << "Result of subtraction: " << positSub.calculate_float_value() << std::endl;
    std::cout << "Result of multiplication: " << positMul.calculate_float_value() << std::endl;
    std::cout << "Result of division: " << positDiv.calculate_float_value() << std::endl;

    // Use the assignment operator
    Posit<short, 16, 3> posit3;
    posit3 = posit1;
    std::cout << "Float value of posit3 (after assignment): " << posit3.calculate_float_value() << std::endl;

    return 0;
}
