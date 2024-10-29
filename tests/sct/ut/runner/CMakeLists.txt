# Result
add_executable(
    TestResult
    TestResult.cpp
    ${CMAKE_TEST_MAIN}
)

target_link_libraries(
    TestResult
    PRIVATE Result
            Logger
            CppUTest
            CppUTestExt
)

add_test(NAME TestResult COMMAND TestResult)
