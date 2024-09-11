add_executable(TestCalculator TestCalculator.cpp main.cpp)

target_link_libraries(TestCalculator PRIVATE Calculator CppUTest CppUTestExt)

add_test(NAME TestCalculator COMMAND TestCalculator)
