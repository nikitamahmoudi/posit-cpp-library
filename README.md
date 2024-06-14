# Posit Cpp Library

A C++ library for handling posit numbers. This library provides functionality for creating posit numbers, performing arithmetic operations on posit numbers, and converting between posit numbers and floating-point values.

## Features

- Create posit numbers from integer and floating-point values.
- Perform arithmetic operations on posit numbers (addition, subtraction, multiplication, division).
- Convert between posit numbers and floating-point values.

## Installation

Clone the repository and navigate to the root directory of the project:

```bash
git clone https://github.com/yourusername/posit-cpp-library.git
cd posit-cpp-library
```

### Building the Library

Assuming you are using CMake, here is how you can build the library and the example:

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

### Example

Here's an example of how to use the `Posit` library:

```cpp
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
```

### Building and Running the Example

1. Create a new file `examples/example.cpp` and copy the example code above into it.
2. Follow the instructions in the `Installation` section to build the library and the example.

To run the example:

```bash
cd build
./example
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
