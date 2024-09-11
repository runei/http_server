#include <iostream>

#include "Calculator.hpp"

int main()
{
    Calculator calculator;

    double a = 10.0, b = 5.0;

    std::cout << "Addition: " << calculator.add(a, b) << std::endl;
    std::cout << "Subtraction: " << calculator.subtract(a, b) << std::endl;
    std::cout << "Multiplication: " << calculator.multiply(a, b) << std::endl;
    std::cout << "Division: " << calculator.divide(a, b) << std::endl;

    return 0;
}
