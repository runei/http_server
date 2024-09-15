#include "CppUTest/TestHarness.h"

#include <stdexcept>

#include "Calculator.hpp"

TEST_GROUP (CalculatorTest)
{
    static constexpr double threshold = 0.000001;

    void setup() override {}

    void teardown() override {}
};

TEST (CalculatorTest, Add)
{
    //Assign
    const double num1     = 10.0;
    const double num2     = 5.0;
    const double expected = 15.0;

    // Act
    auto actual = Calculator::add(num1, num2);

    // Assert
    DOUBLES_EQUAL(expected, actual, threshold);
}

TEST (CalculatorTest, Subtract)
{
    //Assign
    const double num1     = 10.0;
    const double num2     = 5.0;
    const double expected = 5.0;

    // Act
    auto actual = Calculator::subtract(num1, num2);

    // Assert
    DOUBLES_EQUAL(expected, actual, threshold);
}

TEST (CalculatorTest, Multiply)
{
    //Assign
    const double num1     = 10.0;
    const double num2     = 5.0;
    const double expected = 50.0;

    // Act
    auto actual = Calculator::multiply(num1, num2);

    // Assert
    DOUBLES_EQUAL(expected, actual, threshold);
}

TEST (CalculatorTest, Divide)
{
    //Assign
    const double num1     = 10.0;
    const double num2     = 5.0;
    const double expected = 2.0;

    // Act
    auto actual = Calculator::divide(num1, num2);

    // Assert
    DOUBLES_EQUAL(expected, actual, threshold);
}

TEST (CalculatorTest, DivideByZero)
{
    //Assign
    const double num1 = 10.0;
    const double num2 = 0.0;

    // Act and Assert
    CHECK_THROWS(std::invalid_argument, Calculator::divide(num1, num2));
}
