add_executable(TestCalculator TestCalculator.cpp)

target_link_libraries(
    TestCalculator
    Calculator
    CppUTest
    CppUTestExt
)

add_test(NAME TestCalculator COMMAND TestCalculator)
