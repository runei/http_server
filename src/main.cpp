#include <iostream>

#include "Calculator.hpp"

int main()
{
    const double num1 = 10.0;
    const double num2 = 5.0;

    std::cout << "Addition: " << Calculator::add(num1, num2) << std::endl;
    std::cout << "Subtraction: " << Calculator::subtract(num1, num2) << std::endl;
    std::cout << "Multiplication: " << Calculator::multiply(num1, num2) << std::endl;
    std::cout << "Division: " << Calculator::divide(num1, num2) << std::endl;

    return 0;
}
