#pragma once

class Calculator
{
public:
    Calculator()  = default;
    ~Calculator() = default;

    static double add(double a, double b);
    static double subtract(double a, double b);
    static double multiply(double a, double b);
    static double divide(double a, double b);
};
