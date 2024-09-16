#include "CppUTest/TestHarness.h"

TEST_GROUP (CalculatorTest)
{
    static constexpr double threshold = 0.000001;

    void setup() override {}

    void teardown() override {}
};

TEST (CalculatorTest, Add)
{
}
