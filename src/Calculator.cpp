#include "Calculator.hpp"

#include <stdexcept>

double Calculator::add(double num1, double num2)
{
    return num1 + num2;
}

double Calculator::subtract(double num1, double num2)
{
    return num1 - num2;
}

double Calculator::multiply(double num1, double num2)
{
    return num1 * num2;
}

double Calculator::divide(double num1, double num2)
{
    if (num2 == 0)
    {
        throw std::invalid_argument("Division by zero");
    }
    return num1 / num2;
}
