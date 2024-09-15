#pragma once

class Calculator
{
public:
    Calculator()  = default;
    ~Calculator() = default;

    static double add(double num1, double num2);
    static double subtract(double num1, double num2);
    static double multiply(double num1, double num2);
    static double divide(double num1, double num2);
};
