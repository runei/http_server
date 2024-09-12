#include "CppUTest/TestHarness.h"

#include <stdexcept>

#include "Calculator.hpp"

TEST_GROUP (CalculatorTest)
{
    void setup() {}

    void teardown() {}
};

TEST (CalculatorTest, Add)
{
    //Assign
    const double a        = 10.0;
    const double b        = 5.0;
    const double expected = 15.0;

    // Act
    auto actual = Calculator::add(a, b);

    // Assert
    DOUBLES_EQUAL(expected, actual, 0.00001);
}

TEST (CalculatorTest, Subtract)
{
    //Assign
    const double a        = 10.0;
    const double b        = 5.0;
    const double expected = 5.0;

    // Act
    auto actual = Calculator::subtract(a, b);

    // Assert
    DOUBLES_EQUAL(expected, actual, 0.00001);
}

TEST (CalculatorTest, Multiply)
{
    //Assign
    const double a        = 10.0;
    const double b        = 5.0;
    const double expected = 50.0;

    // Act
    auto actual = Calculator::multiply(a, b);

    // Assert
    DOUBLES_EQUAL(expected, actual, 0.00001);
}

TEST (CalculatorTest, Divide)
{
    //Assign
    const double a        = 10.0;
    const double b        = 5.0;
    const double expected = 2.0;

    // Act
    auto actual = Calculator::divide(a, b);

    // Assert
    DOUBLES_EQUAL(expected, actual, 0.00001);
}

TEST (CalculatorTest, DivideByZero)
{
    //Assign
    const double a = 10.0;
    const double b = 0.0;

    // Act and Assert
    CHECK_THROWS(std::invalid_argument, Calculator::divide(a, b));
}
